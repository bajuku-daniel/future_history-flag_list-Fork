<?php

/**
 * @file
 * Contains administrative pages for creating, editing, and deleting flag lists.
 */

/**
 * Flag administration page. Display a list of existing flags.
 */
function flag_lists_admin_page() {
  return theme('flag_lists_admin_page', array('flag' => NULL));
}

/**
 * Theme the output for the main flag administration page.
 */
function theme_flag_lists_admin_page($variables) {
  $flag = $variables['flag'];

  drupal_set_title(t('Flag lists'));
  $output = '<p>' . t('This page shows all the <em>lists</em> that are currently defined on this system.') . '</p>';

  // Can we use our default view?
  if (module_exists('views')) {
    $view = views_get_view('flag_lists', FALSE);
    if (!empty($view)) {
      $view->set_display('default');
      $view->pre_execute();
      $view->execute();
      $output .= $view->render();
    }
  }

  // Else build a simplified display.
  else {
    $header = array(
      array('data' => t('List'), 'field' => 'name'),
      array('data' => t('List title'), 'field' => 'title'),
      array('data' => t('List type')),
      array('data' => t('Owner'), 'field' => 'uid'),
      array('data' => t('Node types')),
      array('data' => t('Operations')),
    );
    $flags = flag_lists_get_flags(25, $header);
    foreach ($flags as $flag) {
      $ops = theme('flag_lists_ops', $flag);

      $name = db_select('users', 'u')
        ->fields('u', array('name'))
        ->condition('uid', $flag->uid)
        ->execute()
        ->fetchField();
      $owner = l($name, 'user/' . $flag->uid, array('attributes' => array('title' => t('View user profile.'))));
      $rows[] = array(
        $flag->name,
        $flag->title,
        $flag->content_type,
        $owner,
        $flag->types ? implode(', ', $flag->types) : '-',
        $ops,
      );
    }
    if (!$flags) {
      $rows[] = array(
        array('data' => t('No flags are currently defined.'), 'colspan' => 6),
      );
    }

    $output .= theme('table', array('header' => $header, 'rows' => $rows));
    $output .= theme('pager', NULL, 25, 0);
  }

  return $output;
}

function flag_lists_add($type = NULL) {
  if (is_null($type)) {
    drupal_access_denied();
  }

  $departure_node = NULL;
  $departure_node_query = drupal_get_query_parameters();
  if (!empty($departure_node_query)){
    $departure_node = explode('/', $departure_node_query['destination']);
    $departure_node = end($departure_node);
  }
  return drupal_get_form('flag_lists_form', NULL, $type, $departure_node);
}

/**
 * Callback for adding new lists through AJAX.
 */
function flag_lists_add_js($type = NULL) {

  $token = $_REQUEST['form_token'];
  if ( is_null($token) || !drupal_valid_token($token, variable_get('flag_lists_name','list'))) {
    drupal_json_output(array('error' => t('Are you using an old link?')));
    exit();
  }

  if (is_null($type)) {
    drupal_json_output(array('error' => t('Type not supplied.')));
    exit();
  }

  $name = $_REQUEST['name'];
  if (!isset($name) || empty($name)) {
    drupal_json_output(array('error' => t('List name not supplied.')));
    exit();
  }

  if (drupal_strlen($name) > 255) {
    drupal_json_output(array('error' => t('List name is too long. Maximum is 255 characters.')));
    exit();
  }

  if (flag_lists_title_exists($name, $type)) {
    drupal_json_output(array('error' => t('You already have a @name with this name for this type of content.', array('@name' => variable_get('flag_lists_name', 'list')))));
    exit();
  }

  if (!isset($account)) {
    $account = $GLOBALS['user'];
  }

  // New flag. Load the template row.
  $query = db_select('flag', 'f');
  $query->leftJoin('flag_lists_types', 'fl', 'f.name = fl.name');
  $query->fields('f')
    ->fields('fl')
    ->condition('fl.type', $type);

  $row = $query->execute()
    ->fetchObject();

  $newflag = flag_flag::factory_by_entity_type('node');

  $flag = $newflag->factory_by_row($row);
  // The template fid becomes the flag_lists parent flag.
  $flag->pfid = $row->fid;
  // The fid is NULL because this is really a new flag.
  $flag->fid = NULL;
  // The name is created in the save function.
  $flag->name = NULL;
  $flag->link_type = 'toggle';
  $flag->title = $name;
  $flag->types = array($type);
  $flag->uid = $account->uid;
  flag_lists_set_messages($flag);

  // Save it.
  flag_lists_save($flag, $account);

  drupal_json_output(array('error' => '', 'flag' => $flag));
}

/**
 * Form to Add or edit a list.
 */
function flag_lists_form($form, $form_state, $name = NULL, $type = NULL, $departure_node = NULL) {
  // First some sanity checks. $name and $type can't both be NULL.
  // There must be a template for this content type.
  if (is_null($name) && is_null($type)) {
    drupal_access_denied();
  }
  if (!flag_lists_template_exists($type) && is_null($name)) {
    return;
  }
  // If name is numeric, then we have the fid, so get the name.
  if (is_numeric($name)) {
    $name = db_select('flag_lists_flags', 'f')
      ->fields('f', array('name'))
      ->condition('fid', $name)
      ->execute()
      ->fetchField();
  }
  // Adding a new list.
  if (!isset($name)) {
    drupal_set_title(t('Add a new @name', array('@name' => variable_get('flag_lists_name', 'list'))));
    $form['edit'] = array(
      '#type' => 'hidden',
      '#value' => FALSE,
    );
  }

  // Editing an existing list.
  else {
    $flag = flag_lists_get_flag($name);
    $title_string_name = t('@name', array('@name' => variable_get('flag_lists_name', 'list')));
    $title_string = t('Edit your "@title" @name title', array('@title' => $flag->get_title(), '@name' => $title_string_name));
    drupal_set_title();

    $form['edit'] = array(
      '#type' => 'hidden',
      '#value' => TRUE,
    );
    $form['name'] = array(
      '#type' => 'hidden',
      '#value' => $name,
    );
  }

  /*
  * Daniel Frings: ask if we have a departure node to put in the new list
  */
  if ($departure_node != NULL) {
    $form['departure_node'] = array(
      '#type' => 'hidden',
      '#value' => $departure_node,
    );
  }
  else {
    $form['departure_node'] = array(
      '#type' => 'hidden',
      '#value' => NULL,
    );
  }
  $tour_link_id = 0;
  if (isset($flag)) {
    $tour_link_id = $flag->fid;
  }

  $form['header'] = array(
    '#type' => 'markup',
    '#markup' => '<div class="tour_edit_header"><h4>Meine Tour bearbeiten</h4><a href="/de/user/touren">Meine Touren auflisten</a> | <a href="/de/flag/lists/' .$tour_link_id. '">Tour anzeigen</a></div>',
    '#weight' => -4,
  );

    $form['header_commercial'] = array(
      '#type' => 'markup',
      '#markup' => '<div class="tour_edit_header_commercial"><a href="#sort_order">Bildreihenfolge bearbeiten</a></div>',
      '#weight' => -3,
    );

  $form['title'] = array(
    '#type' => 'textfield',
    '#title' => t('Title'),
    '#default_value' => empty($flag->title) ? '' : $flag->title,
    '#description' => t('A short, descriptive title for this @name list. Limit to 45 characters.', array('@name' => variable_get('flag_lists_name', 'list'))),
    '#maxlength' => 45,
    '#required' => TRUE,
    '#access' => empty($flag->locked['title']),
    '#size' => 45,
    '#weight' => -2,
  );


// Daniel Frings: add description, period start and end
 $form['description'] = array(
    '#type' => 'textarea',
    '#title' => t('Description'),
    '#default_value' => empty($flag->description) ? '' : $flag->description,
    '#description' => t('A Description for this @name Tour. Limit to 600 characters.', array('@name' => variable_get('flag_lists_name', 'list'))),
    '#maxlength' => 600,
    '#maxlength_js' => TRUE,
    '#required' => TRUE,
    '#access' => empty($flag->locked['title']),
    '#weight' => -1,
  );

  $form['manual_date'] = array(
    '#type' => 'checkbox',
    '#title' => t('Overwrite Date'),
    '#default_value' => empty($flag->manual_date) ? '' : $flag->manual_date,
    '#description' => t('Override the Auto Date Value'),
    '#access' => empty($flag->locked['title']),
    '#weight' => 1,
    '#ajax' => array(
      'callback' => 'flag_lists_form_date_callback',
      'wrapper' => 'manual_date',
    ),
  );

  $form['dates'] = array(
    '#prefix' => '<div id="manual_date">',
    '#suffix' => '</div>',
    '#type' => 'container',
    '#description' => t('This is where we put our dates'),
    '#weight' => 2,
  );
  if ( (!isset($form_state['values']['manual_date']) && $form['manual_date']['#default_value'] == 1) || (isset($form_state['values']['manual_date']) && $form_state['values']['manual_date'] == 1 )  ) {
    $form['dates']['period_start'] = array(
      '#type' => 'textfield',
      '#title' => t('Period start Year'),
      '#default_value' => empty($flag->period_start) ? '' : $flag->period_start,
      '#description' => t('The Period Start Year of the @name Tour.', array('@name' => variable_get('flag_lists_name', 'list'))),
      '#maxlength' => 45,
      '#required' => TRUE,
      '#disabled' => FALSE,
      '#access' => empty($flag->locked['title']),
      '#size' => 10,
      '#weight' => 1,
    );
    $form['dates']['period_end'] = array(
      '#type' => 'textfield',
      '#title' => t('Period end Year'),
      '#default_value' => empty($flag->period_end) ? '' : $flag->period_end,
      '#description' => t('The Period end Year of the @name Tour.', array('@name' => variable_get('flag_lists_name', 'list'))),
      '#maxlength' => 45,
      '#required' => TRUE,
      '#disabled' => FALSE,
      '#access' => empty($flag->locked['title']),
      '#size' => 10,
      '#weight' => 2,
    );
  }
  else if ( (!isset($form_state['values']['manual_date']) && $form['manual_date']['#default_value'] == 0 ) ) {
    $form['dates']['period_start'] = array(
      '#type' => 'textfield',
      '#title' => t('Period start Year'),
      '#default_value' => empty($flag->period_start) ? '' : $flag->period_start,
      '#description' => t('The Period Start Year of the @name Tour.', array('@name' => variable_get('flag_lists_name', 'list'))),
      '#maxlength' => 45,
      '#required' => TRUE,
      '#access' => empty($flag->locked['title']),
      '#size' => 10,
      '#weight' => 1,
      '#disabled' => TRUE,
    );
    $form['dates']['period_end'] = array(
      '#type' => 'textfield',
      '#title' => t('Period end Year'),
      '#default_value' => empty($flag->period_end) ? '' : $flag->period_end,
      '#description' => t('The Period end Year of the @name Tour.', array('@name' => variable_get('flag_lists_name', 'list'))),
      '#maxlength' => 45,
      '#required' => TRUE,
      '#access' => empty($flag->locked['title']),
      '#size' => 10,
      '#weight' => 2,
      '#disabled' => TRUE,
    );
  }
  else if ( $form_state['values']['manual_date'] == 0 ) {
    $tour_dates = flag_lists_set_date($id = NULL, $flag, 'renew');
    $form['dates']['period_start'] = array(
      '#type' => 'textfield',
      '#title' => t('Period start Year new calculated'),
      '#default_value' => $tour_dates['start'],
      '#description' => t('The Period Start Year of the @name Tour.', array('@name' => variable_get('flag_lists_name', 'list'))),
      '#maxlength' => 45,
      '#required' => TRUE,
      '#access' => empty($flag->locked['title']),
      '#size' => 10,
      '#weight' => 1,
      '#disabled' => TRUE,
    );

    $form['dates']['period_end'] = array(
      '#type' => 'textfield',
      '#title' => t('Period end Year new calculated'),
      '#default_value' => $tour_dates['end'],
      '#description' => t('The Period end Year of the @name Tour.', array('@name' => variable_get('flag_lists_name', 'list'))),
      '#maxlength' => 45,
      '#required' => TRUE,
      '#access' => empty($flag->locked['title']),
      '#size' => 10,
      '#weight' => 2,
      '#disabled' => TRUE,
    );
  }

  $form['tour_distance'] = array(
    '#type' => 'hidden',
    '#title' => t('Tour Distance'),
    '#default_value' => empty($flag->tour_distance) ? '' : $flag->tour_distance,
    '#description' => t('The Distance of the @name Tour.', array('@name' => variable_get('flag_lists_name', 'list'))),
    '#maxlength' => 10,
    '#required' => FALSE,
    '#access' => empty($flag->locked['title']),
    '#disabled' => FALSE,
    '#size' => 10,
    '#weight' => 4,
  );
  //
  // $form['remove_node_ids'] = array(
  //   '#type' => 'textfield',
  //   '#title' => t('Items to remove from Tour'),
  //   '#required' => FALSE,
  //   '#access' => empty($flag->locked['title']),
  //   '#disabled' => FALSE,
  // );


  /*
  *  DF: add the Tour Sort functionality to the edit tour form
  */
  $rows = array();
  $row_elements = array();

  // Put it into a fieldset for no reason.
  $form['data_table'] = array(
    '#type' => 'fieldset',
    '#title' => '<span id="sort_order"></span>' . t('Change POI Order'),
    '#weight' => 5,
  );

  // Collect our data.
  if (isset($flag)) {
    $table_data = flag_lists_get_node_list_edit_values($flag);

    foreach ($table_data as $node_detail) {
      $node_id = $node_detail['entity_id'];
      $stadt_term = taxonomy_term_load($node_detail['node_details']->field_stadt['und'][0]['tid']);
      $stadt = $stadt_term->name;

      $data[$node_id] = array(
        'weight' => $node_detail['weight'],
        'name' => $node_detail['node_details']->title,
        'lat' => $node_detail['node_details']->field_position_der_aufnahme['und'][0]['lat'],
        'lng' => $node_detail['node_details']->field_position_der_aufnahme['und'][0]['lng'],
        'year' => $node_detail['node_details']->field_jahr['und'][0]['value'],
        'picture' => theme('image_style', array('path' => $node_detail['node_details']->field_bild['und'][0]['uri'], 'style_name' => 'thumbnail')),
        'stadt' => $stadt,
      );
    }
    // Build the rows.
    foreach ($data as $id => $entry) {
      // Build the table rows.
      $rows[$id] = array(
        'data' => array(
          // Cell for the cross drag&drop element.
          array('class' => array('entry-cross')),
          // Weight item for the tabledrag.
          array('data' => array(
            '#type' => 'weight',
            '#title' => t('Weight'),
            '#title_display' => 'invisible',
            '#default_value' => $entry['weight'],
            '#parents' => array('data_table', $id, 'weight'),
            '#attributes' => array(
              'class' => array('entry-order-weight'),
            ),
          )),
          // Entry picture.
          $entry['picture'],
          // Name textfield.
          check_plain($entry['name']) . ' | ' . $entry['year'],
          $entry['stadt'],

        ),

        'class' => array('draggable'),
        'id' => $id,
        'lat_value' => $entry['lat'],
        'lng_value' => $entry['lng'],
        'name' =>   check_plain($entry['name']),
        'year' => $entry['year'],
      );
      // Build rows of the form elements in the table.
      $row_elements[$id] = array(
        'weight' => &$rows[$id]['data'][1]['data'],
      //  'name' => &$rows[$id]['data'][2]['data'],
      );
    }

    // Add the table to the form.
    $form['data_table']['table'] = array(
      '#theme' => 'table',
      // The row form elements need to be processed and build,
      // therefore pass them as element children.
      'elements' => $row_elements,
      '#header' => array(
        // We need two empty columns for the weigth field and the cross.
        array('data' => NULL, 'colspan' => 2),
        t('Picture'),
        t('Name | Jahr'),
        t('Stadt'),
      ),
      '#rows' => $rows,
      '#empty' => t('There are no entries available.'),
      '#attributes' => array('id' => 'entry-order'),
    );
    drupal_add_tabledrag('entry-order', 'order', 'sibling', 'entry-order-weight');
  }

  $form['#attached']['js'][] = drupal_get_path('module', 'flag_lists') . '/js/infobox.js';
  $form['#attached']['css'][] = drupal_get_path('module', 'flag_lists') . '/css/flag_lists.css';
  $form['#attached']['js'][] = drupal_get_path('module', 'flag_lists') . '/js/flag_lists_map.js';

  $form['googlemap'] = array(
    '#type' =>'markup',
    '#markup' =>'<div id="futurehistory-tour-edit-map" class="futurehistory" style="width:100%;height:700px;display:block;margin-bottom:50px;margin-top:30px;"></div>',
    '#weight' => 6,
  );

  //Add the comercial tour form fields
  global $user;
  $user_roles = $user->roles;
  $commercial_tour_roles_accepted = array('Touren Anbieter','administrator');
  $admin_user_role = array('administrator');

  if (array_intersect($commercial_tour_roles_accepted, $user_roles)) {
    $commercial_tour_id = 0;
    if (isset($flag)) {
      $commercial_tour_fid = $flag->fid;
//      $commercial_tour_deeplink = 'https://x5b33.app.goo.gl/?apn=com.extendedvision.futurehistory&link=https://www.future-history.eu/flag/lists/'.$commercial_tour_fid.'?tour_id=' . $commercial_tour_fid;
//      $commercial_tour_deeplink = 'https://x5b33.app.goo.gl/?apn=com.extendedvision.futurehistory&ibi=com.extended-vision.futurehistory&isi=1034236058&link=https://www.future-history.eu/flag/lists/'.$commercial_tour_fid.'?tour_id=' . $commercial_tour_fid;
//      $commercial_tour_deeplink = 'https://x5b33.app.goo.gl/?apn=com.extendedvision.futurehistory&link=http://dev-daniel.future-history.eu/flag/lists/'.$commercial_tour_fid.'?tour_id=' . $commercial_tour_fid;

      $commercial_tour_deeplink = 'https://x5b33.app.goo.gl/?apn=com.extendedvision.futurehistory&ibi=com.extended-vision.futurehistory&isi=1034236058&link=http://dev.future-history.eu/flag/lists/'.$commercial_tour_fid.'?tour_id=' . $commercial_tour_fid;
      $commercial_tour_purchase_id = 'eu.futurehistory.tour.' . $commercial_tour_fid;
    }

    //change the header with commercial tour anchor
    $form['header_commercial']['#markup'] = '<div class="tour_edit_header_commercial"><a href="#sort_order">Bildreihenfolge bearbeiten</a> | <a href="#communicate">Tour planen und kommunizieren</a> </div>';


    $tour_types = array(
      '1' => t('mit Gästeführer (für öffentliche und gebuchte Gruppenführungen)'),
      '2' => t('selbstgeführte App-Tour (für Einzelbucher und Kleingruppen)'),
    );

    if ($flag->tour_type == '0' || empty($flag->tour_type)) {
      $tour_type_default_value = '1';
    } else {
      $tour_type_default_value = $flag->tour_type;
    }

    $form['tour_type'] = array(
      '#type' => 'radios',
      '#title' => '<span id="communicate"></span>' . t('Art der Tour'),
      '#options' => $tour_types,
      '#description' => t('Only for Comercial Tours: select your Tour Type'),
      '#default_value' => $tour_type_default_value,
      '#weight' => 7,
      '#ajax' => array(
        'callback' => 'flag_lists_form_commercial_tour_callback',
        'wrapper' => 'commercial_tour',
      ),
    );

    $form['commercial_tour'] = array(
      '#prefix' => '<div id="commercial_tour">',
      '#suffix' => '</div>',
      '#type' => 'container',
      '#description' => t('This is where we put our commercial tour info'),
      '#weight' => 8,
    );

    $form['commercial_tour_add_help'] = array(
      '#type' =>'hidden',
      '#markup' =>t('<div class="tour_add_help"><p>Die weiteren Einstellungen sowie Informationen zur Kommunikation und Veröffentlichung der Touren können nach dem ersten Speichern im Profilbereich unter "Meine Touren" eingesehen werden.</p></div>'),
      '#weight' => 9,
    );

    if ( (!isset($form_state['values']['tour_type']) && $form['tour_type']['#default_value'] == 2) || (isset($form_state['values']['tour_type']) && $form_state['values']['tour_type'] == 2 )  ) {
      $form['commercial_tour']['tour_price'] = array(
        '#type' => 'textfield',
        '#title' => t('Preis der Tour'),
        '#default_value' => empty($flag->tour_price) ? '' : $flag->tour_price,
        '#description' => t('in EUR inkl. 19% Mehrwertsteuer'),
        '#maxlength' => 8,
        '#required' => false,
        '#access' => empty($flag->locked['title']),
        '#size' => 8,
        '#weight' => 1,
        '#disabled' => false,
      );
      $form['commercial_tour']['android_purchase_id'] = array(
        '#type' => 'textfield',
        '#title' => t('Purchase ID '),
        '#default_value' => empty($flag->android_purchase_id) ? $commercial_tour_purchase_id : $flag->android_purchase_id,
        '#description' => t('Purchase ID for the APP Store. Only visible for the FH - Administrator.'),
        '#maxlength' => 32,
        '#required' => false,
        '#access' => empty($flag->locked['title']),
        '#size' => 10,
        '#weight' => 4,
        '#disabled' => true,
      );
    }
    //shorten the tour deeplink with the firebase API
    $firebas_api_url = 'https://firebasedynamiclinks.googleapis.com/v1/shortLinks?key=AIzaSyA48yhSN-9HEswUNK_SpzhbqQO-xq5o2_0';
    $firebase_data = array('longDynamicLink' => $commercial_tour_deeplink);

    // use key 'http' even if you send the request to https://...
    $firebase_options = array(
        'http' => array(
            'header'  => "application/json\r\n",
            'method'  => 'POST',
            'content' => http_build_query($firebase_data)
        )
    );
    if (empty($flag->tour_deeplink)) {
      $firebase_context  = stream_context_create($firebase_options);
      $short_deeplink_json = file_get_contents($firebas_api_url, false, $firebase_context);
      $short_deeplink = json_decode($short_deeplink_json);
    } else {
      $short_deeplink->shortLink = $flag->tour_deeplink;
    }

    $form['commercial_tour']['tour_deeplink'] = array(
      '#type' => 'hidden',
      '#title' => t('Tour Deeplink'),
      '#default_value' => empty($flag->tour_deeplink) ? $short_deeplink->shortLink : $flag->tour_deeplink,
      '#description' => t('The deeplink to publish the Tour to your Clients'),
      '#maxlength' => 255,
      '#required' => false,
      '#access' => empty($flag->locked['title']),
      '#size' => 10,
      '#weight' => 2,
      '#disabled' => false,
    );

    //markup for deeplinks
    $google_qr_deeplink_url = $short_deeplink->shortLink;
    $google_qr_image_url = 'https://chart.googleapis.com/chart?chs=300x300&cht=qr&chl='. $google_qr_deeplink_url . '&chld=H|0&choe=UTF-8';

    $form['commercial_tour']['tour_qrcode'] = array(
      '#type' => 'hidden',
      '#title' => t('Tour QR Code'),
      '#default_value' => empty($flag->tour_qrcode) ? $google_qr_image_url : $flag->tour_qrcode,
      '#description' => t('The Link to the QR code to generate an image'),
      '#maxlength' => 255,
      '#required' => false,
      '#access' => empty($flag->locked['title']),
      '#size' => 10,
      '#disabled' => false,
    );

    $google_qr_alt
      = t('QR Code for @url', array(
        '@url' => $google_qr_deeplink_url));

    $google_qr_code_img = theme('image', array(
      'path' => $google_qr_image_url,
      'alt' => $google_qr_alt,
      'attributes' => array('class' => 'googleQRcode'),
    ));

    $tour_deeplink_qr_code_markup = '<div class="deeplink_wrapper"><label>Direktlink zur Tour</label> <p>Direktlink zur Installation der APP und zum Öffnen der Tour: <br><b>' . $google_qr_deeplink_url . '</b><br><small> Diesen Link auf Ihre Website platzieren und per E-Mail an die Teilnehmer Ihrer Tour senden.</small></p></div><div class="qr_code_wrapper"><br><label>QR-Code zur Tour</label><p>QR-Code zur Installation der APP und zum Öffnen der Tour:<br><br>' . $google_qr_code_img . '<br><small>Diesen QR-Code auf Ihre Print Produkte platzieren und als E-Mail Anhang an die Teilnehmer Ihrer Tour senden.</small></div>';


    $form['commercial_tour']['tour_deeplink_qr_code'] = array(
      '#type' =>'markup',
      '#title' => t('Tour Deeplink & QR Code'),
      '#markup' => $tour_deeplink_qr_code_markup,
      '#weight' => 3,
    );



//    $tour_deactivation_markup = '<div class="deactivation_message"><p>Um diese Tour zu Deaktivieren sende bitte eine Email an: <a href="mailto:info@future-history.eu">info@future-history.eu</a>. Wir werden die Tour für dich in den Appstores deaktivieren - die Tour bleibt für Benutzer die sie gekauft haben trotzdem benutzbar.</p></div>';
    $tour_deactivation_markup = '<div class="deactivation_message"><p>Zur Deaktivierung dieser Tour bitte eine Email an: <a href="touren@future-history.eu">info@future-history.eu</a> senden. Wir werden die Tour anschliessend im Google Play Store und Apple App Store deaktivieren, so dass keine weiteren Käufe möglich sind. Bereits getätigte Käufe dieser Tour bleiben davon unberührt und können weiterhin zum Aufruf der Tour genutzt werden.</p></div>';

    $form['commercial_tour']['deactivation_message'] = array(
      '#type' =>'markup',
      '#title' => t('Tour Deeplink & QR Code'),
      '#markup' => $tour_deactivation_markup,
      '#weight' => 4,
    );

    $tour_status = array(
      '0' => t('Inaktiv'),
      '1' => t('Aktiv'),
    );

    $form['commercial_tour']['tour_status'] = array(
      '#type' => 'radios',
      '#title' => t('Tour Status'),
      '#description' => t('The Tour Status - only visible for the FH - Administrator.' ),
      '#options' => $tour_status,
      '#default_value' => $flag->tour_status ,
      '#weight' => 5,
      '#disabled' => true,
    );
  } else {
    // set default values if not commercial tour user
    $form['tour_type'] = array(
      '#type' => 'hidden',
      '#title' => t('Art der Tour'),
      '#default_value' => '0',
    );
    $form['tour_status'] = array(
      '#type' => 'hidden',
      '#title' => t('Status der Tour'),
      '#default_value' => '1',
    );
  }

  if (($form['edit']['#value'] == TRUE) && (array_intersect($admin_user_role, $user_roles))) {
    $form['commercial_tour']['tour_status']['#disabled'] = false;
    $form['commercial_tour']['android_purchase_id']['#disabled'] = false;
  }


  if ($form['edit']['#value'] == FALSE) {
    $form['dates']['period_start']['#type'] = 'hidden';
    $form['dates']['period_end']['#type'] = 'hidden';
    $form['dates']['#type'] = 'hidden';
    $form['manual_date']['#type'] = 'hidden';
    $form['tour_distance']['#disabled'] = FALSE;
    $form['data_table']['#type'] = 'hidden';
    $form['googlemap']['#type'] = 'hidden';
    $form['header']['#markup'] = '<div class="tour_edit_header"><h4>Neue Tour erstellen</h4></div>';
    $form['header_commercial']['#type'] = 'hidden';
    $form['commercial_tour']['tour_price']['#type'] = 'hidden';
    $form['commercial_tour']['android_purchase_id']['#type'] = 'hidden';
    $form['commercial_tour']['tour_deeplink']['#type'] = 'hidden';
    $form['commercial_tour']['tour_status']['#type'] = 'hidden';
    $form['commercial_tour']['tour_deeplink_qr_code']['#type'] = 'hidden';
    $form['commercial_tour']['deactivation_message']['#type'] = 'hidden';
    $form['commercial_tour_add_help']['#type']='markup';

  }
  $form['type'] = array(
    '#type' => 'hidden',
    '#value' => $type,
  );

  $form['abort'] = array(
    '#type' => 'markup',
    '#markup' => '<a href="#" onclick="window.history.go(-1); return false;" class="btn btn-warning form-submit">Abbrechen</a>',
    '#weight' => 10,
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('<span class="icon glyphicon glyphicon-ok" aria-hidden="true"></span> Speichern'),
    '#weight' => 11,
    '#attributes' => array(
      'class' => array('ansicht-submit-green'),
    ),
  );

  return $form;
}

function flag_lists_form_date_callback($form, $form_state){
  return $form['dates'];
}

function flag_lists_form_commercial_tour_callback($form, $form_state){
  return $form['commercial_tour'];
}

/**
 * Validate a list.
 */
function flag_lists_form_validate($form, $form_state) {
  // Ensure 255 charactor or less name.
  if (drupal_strlen($form_state['values']['title']) > 45) {
    form_set_error('name', t('The @name title may only be 45 characters long.', array('@name' => variable_get('flag_lists_name', 'list'))));
  }
 if (drupal_strlen($form_state['values']['description']) > 600) {
    form_set_error('name', t('The @name description may only be 600 characters long.', array('@name' => variable_get('flag_lists_name', 'list'))));
  }
  // Ensure the machine name is unique.
  if (!$form_state['values']['edit']) {
    if (flag_lists_title_exists($form_state['values']['title'], $form_state['values']['type'])) {
      form_set_error('title', t('You already have a @name with this name for this type of content.', array('@name' => variable_get('flag_lists_name', 'list'))));
    }
  }
}

/**
 * Save a list.
 */
function flag_lists_form_submit($form, $form_state, $account = NULL) {
  if (!isset($account)) {
    $account = $GLOBALS['user'];
  }

  if (!empty($form_state['values']['edit'])) {
    $flag = flag_lists_get_flag($form_state['values']['name']);
    $flag->title = $form_state['values']['title'];
    $flag->description = $form_state['values']['description'];
    $flag->manual_date = $form_state['values']['manual_date'];
    $flag->period_start = $form_state['values']['period_start'];
    $flag->period_end = $form_state['values']['period_end'];
    $flag->tour_distance = $form_state['values']['tour_distance'];
    $flag->departure_node = $form_state['values']['departure_node'];
    $flag->tour_type = $form_state['values']['tour_type'];
    $flag->tour_price = $form_state['values']['tour_price'];
    $flag->android_purchase_id = $form_state['values']['android_purchase_id'];
    $flag->tour_deeplink = $form_state['values']['tour_deeplink'];
    $flag->tour_qrcode = $form_state['values']['tour_qrcode'];
    $flag->tour_status = intval($form_state['values']['tour_status']);
    $flag->tour_type = intval($form_state['values']['tour_type']);
    flag_lists_set_messages($flag);
    flag_lists_save($flag);
    flag_lists_node_list_save_weight($flag, $form_state['input']['data_table']);
    flag_lists_get_distance($id = NULL, $flag, $action = 'renew');
    _flag_lists_clear_cache();

  }
  else {
    // New flag. Load the template row.
    $type = $form_state['values']['type'];
    $query = db_select('flag', 'f');
    $query->leftJoin('flag_lists_types', 'fl', 'f.name = fl.name');
    $query->fields('f')
      ->fields('fl')
      ->condition('fl.type', $type);
    $row = $query->execute()
      ->fetchObject();
    $newflag = flag_flag::factory_by_entity_type('node');

    $flag = $newflag->factory_by_row($row);
    // The template fid becomes the flag_lists parent flag.
    $flag->pfid = $row->fid;
    // The fid is NULL because this is really a new flag.
    $flag->fid = NULL;
    // The name is created in the save function.
    $flag->name = NULL;
    $flag->link_type = 'toggle';
    $flag->title = $form_state['values']['title'];
    $flag->description = $form_state['values']['description'];
    $flag->types = array($type);
    $flag->uid = $account->uid;
    $flag->description = $form_state['values']['description'];
    $flag->manual_date = intval($form_state['values']['manual_date']);
    $flag->period_start = $form_state['values']['period_start'];
    $flag->period_end = $form_state['values']['period_end'];
    $flag->tour_distance = $form_state['values']['tour_distance'];
    $flag->departure_node = $form_state['values']['departure_node'];
    $flag->tour_price = $form_state['values']['tour_price'];
    $flag->android_purchase_id = $form_state['values']['android_purchase_id'];
    $flag->tour_deeplink = $form_state['values']['tour_deeplink'];
    $flag->tour_qrcode = $form_state['values']['tour_qrcode'];
    $flag->tour_status = 1;
    $flag->tour_type = intval($form_state['values']['tour_type']);


    flag_lists_set_messages($flag);
    drupal_set_message(t('New Tour added'));
    // Save it.
    flag_lists_save($flag, $account);

  }
}

/**
 * Flag lists settings page.
 */
function flag_lists_settings_form($form, $form_state) {
  drupal_set_title(t('Flag lists settings'));
  $form['text'] = array(
    '#title' => t('Using flag lists'),
    '#markup' => t('Flag lists allow users to create their own personal flags.
      No user can add to another user\'s lists. Lists inherit their
      settings from template flags, which exist as flags in the flags\' module.'
    ),
  );

  $form['flag_lists_name'] = array(
    '#type' => 'textfield',
    '#title' => t('Substitute "list" with your own terminology'),
    '#default_value' => t('@name', array('@name' => variable_get('flag_lists_name', 'list'))),
    '#description' => t('You can choose to use another name for "list", such as "favorites" or "bookmarks". Lowercase and plural names usually work best.'),
    '#required' => TRUE,
  );
  $form['rebuild'] = array(
    '#type' => 'fieldset',
    '#title' => t('Global rebuild'),
    '#description' => t('Changes to list templates and  settings normally apply
      to only newly created flags. However, you can globally apply changes here.
      First adjust the settings above and the list templates and save them. Then
      click the link below. This will change ALL existing flag lists. It cannot
      be undone.'),
    '#tree' => FALSE,
  );
  $form['rebuild']['global_rebuild'] = array(
    '#markup' => l(t('Rebuild all flag lists.'), FLAG_ADMIN_PATH . '/flag-lists/rebuild'),
  );

  return system_settings_form($form);
}

/**
 * Confirm global settings rebuild.
 */
function flag_lists_rebuild_confirm($form, $form_state) {
  return confirm_form($form,
    t('Are you sure you want to rebuild all flag lists?'),
    FLAG_ADMIN_PATH . '/lists/settings',
    t('This action cannot be undone.'),
    t('Rebuild'), t('Cancel')
  );
}

/**
 * Confirm global settings rebuild.
 */
function flag_lists_rebuild_confirm_submit($form, $form_state) {
  flag_lists_rebuild();
  drupal_set_message(t('All flag lists have been rebuilt.'));
  drupal_goto(FLAG_ADMIN_PATH . '/lists/settings');
}

/**
 * Delete flag lists page.
 */
function flag_lists_delete_confirm($form, $form_state, $name) {
  $flag = flag_lists_get_flag($name);
  if (empty($flag)) {
    drupal_goto();
  }

  $form['fid'] = array('#type' => 'value', '#value' => $flag->fid);

  return confirm_form($form,
    t('Are you sure you want to delete @title?', array('@title' => $flag->get_title())),
    isset($_GET['destination']) ? $_GET['destination'] : '/',
    t('This action cannot be undone.'),
    t('Delete'), t('Cancel')
  );
}

function flag_lists_delete_confirm_submit($form, &$form_state) {
  $flag = flag_lists_get_flag($form_state['values']['fid']);
  if ($form_state['values']['confirm']) {
    flag_lists_fl_delete($flag);
  }
}

/**
 * Form to create a new template.
 */
function flag_lists_create_template_form($form, $form_state) {
  drupal_set_title(t('Add a new @name template', array('@name' => variable_get('flag_lists_name', 'list'))));
  $form['help'] = array(
    '#value' => t('This form creates a new, blank list template. After saving, you will be able to configure further options.'),
  );
  $form['name'] = array(
    '#type' => 'textfield',
    '#title' => t('Template name'),
    '#description' => t('The machine-name for this template. It may be up to 20 characters long and my only contain lowercase letters, underscores, and numbers.'),
    '#maxlength' => 255,
    '#required' => TRUE,
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );
  return $form;
}

/**
 * New template validation.
 */
function flag_lists_create_template_form_validate($form, &$form_state) {
  // Ensure a safe machine name.
  if (!preg_match('/^[a-z_][a-z0-9_]*$/', $form_state['values']['name'])) {
    form_set_error('name', t('The flag name may only contain lowercase letters, underscores, and numbers.'));
  }
  // Ensure 20 charactor or less name.
  if (drupal_strlen($form_state['values']['name']) > 20) {
    form_set_error('name', t('The flag name may only be 20 characters long.'));
  }
  // Ensure the machine name is unique.
  $flag = flag_get_flag('fl_template_' . $form_state['values']['name']);
  if ($flag) {
    form_set_error('name', t('Flag names must be unique. This flag name is already in use.'));
  }
}

/**
 * New template submit.
 */
function flag_lists_create_template_form_submit($form, &$form_state) {
  $template = flag_lists_flag_default_flags();
  $flag = flag_flag::factory_by_array(array_shift($template));
  $flag->title = t('Flag list template') . ' ' . $form_state['values']['name'];
  $flag->name =  'fl_template_' . $form_state['values']['name'];
  $flag->save();
  // Enter the new template into flag_lists_types.
  db_insert('flag_lists_types')
    ->fields(array(
      'name' => $flag->name,
    ))
    ->execute();
  drupal_set_message(t('You must save the template below otherwise the functionality is not guaranteed!'), 'warning');
  $form_state['redirect'] = FLAG_ADMIN_PATH . '/manage/' . $flag->name;
}


/**
 * Developer tool to generate dummy lists and listings.
 */

// @todo use batch api.
function flag_lists_generate_lists_form() {
  $templates = flag_lists_get_templates();
  $options = array();
  foreach ($templates as $template) {
    $options[$template->fid] = $template->name . ' (' . implode(', ', $template->types) . ')';
  }
  $form['templates'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Generate lists and/or listings for the following templates.'),
    '#options' => $options,
  );

  $form['lists'] = array(
    '#type' => 'textfield',
    '#title' => t('How many lists should be generated?'),
    '#default_value' => '0',
    '#size' => 7,
    '#maxlength' => 7,
  );

  $form['listings'] = array(
    '#type' => 'textfield',
    '#title' => t('How many listings should be generated?'),
    '#default_value' => '0',
  );

  $form['kill_lists'] = array(
    '#type' => 'checkbox',
    '#title' => t('Delete ALL existing lists and listings before generating new ones? Templates will not be deleted.'),
    '#default_value' => FALSE,
  );
  $form['kill_listings'] = array(
    '#type' => 'checkbox',
    '#title' => t('Delete ALL existing listings before generating new ones? (Lists are not deleted unless the above is checked.)'),
    '#default_value' => FALSE,
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Do it!'),
  );
  return $form;
}

/**
 * Validation handler for flag_lists_generate_lists_form.
 */
function flag_lists_generate_lists_form_validate($form, &$form_state) {
  if ($form_state['values']['lists'] && !is_numeric($form_state['values']['lists']) || $form_state['values']['lists'] < 0) {
    form_set_error('lists', t('Number of lists to generate must be a number, 1 or more.'));
  }
  if ($form_state['values']['listings'] && !is_numeric($form_state['values']['listings']) || $form_state['values']['listings'] < 0) {
    form_set_error('listings', t('Number of listings to generate must be a number, 1 or more.'));
  }
  if ($form_state['values']['lists'] > 0 && !count(array_filter($form_state['values']['templates']))) {
    form_set_error('templates', t('You must select at least 1 template for the lists to be genereated'));
  }
  if ($form_state['values']['listings'] > 0 && !count(array_filter($form_state['values']['templates']))) {
    form_set_error('templates', t('You must select at least 1 template for the listings to be genereated'));
  }
}

/**
 * Submit handler for flag_lists_generate_lists_form.
 */
function flag_lists_generate_lists_form_submit($form, &$form_state) {
  global $user;
  module_load_include('inc', 'devel_generate');

  // Delete listings.
  if ($form_state['values']['kill_listings']) {
    $flags = flag_lists_get_flags();
    foreach ($flags as $flag) {
      $result = db_select('flag_lists_content', 'f')
        ->fields('f', array('fcid', 'entity_id'))
        ->condition('fid', $flag->fid)
        ->execute();

      foreach ($result as $row) {
        db_delete('flag_lists_content')->condition('fid', $flag->fid)->execute();
        db_delete('flag_lists_counts')->condition('fid', $flag->fid)->execute();

        module_invoke_all('flag', 'unflag', $flag, $row->entity_id, $account, $row->fcid);
      }
    }
    drupal_set_message(t('All listings were deleted.'));
  }

  // Delete lists and listings.
  if ($form_state['values']['kill_lists']) {
    // If we loaded all flags above, don't reload them here.
    if (!count($flags)) {
      $flags = flag_lists_get_flags();
    }
    foreach ($flags as $flag) {
      flag_lists_fl_delete($flag, $user);
    }
    drupal_set_message(t('All lists and their listings were deleted.'));
  }


  $templates = array_filter($form_state['values']['templates']);
  $uids = array_filter(devel_get_users()); // Don't use the anon user.

  // Generate lists.
  if ($form_state['values']['lists'] && count($templates)) {
    for ($i = 1; $i <= $form_state['values']['lists']; $i++) {
      $template = flag_get_flag(NULL, array_rand($templates));
      $account->uid = $uids[array_rand($uids)];
      $edit['values']['title'] = devel_create_greeking(7, TRUE);
      $edit['values']['type'] = $template->types[array_rand($template->types)];
      $form = array();
      flag_lists_form_submit($form, $edit, $account);
    }
    drupal_set_message(t('@lists created.', array('@lists' => format_plural($form_state['values']['lists'], '1 list', '@count lists'))));
  }

  // Generate listings.
  if ($form_state['values']['listings']) {

    $count = 0;

    for ($i = 1; $i <= $form_state['values']['listings']; $i++) {
      $account->uid = $uids[array_rand($uids)];
      $lists = flag_lists_get_user_flags(NULL, $account);

      // Remove any lists that don't use the chosen templates.
      foreach ($lists as $key => $list) {
        if (!isset($templates[$list->pfid])) {
          unset($lists[$key]);
        }
      }

      // Ensure user has lists.
      if (!count($lists)) {
        continue;
      }

      $list = $lists[array_rand($lists)];
      $content_type = $list->types[array_rand($list->types)];

      // We get the random nid with 2 SELECTS to avoid slow ORDER BY Rand().
      // Get max nid for our content type.
      $query = db_select('node')
        ->condition('type', $content_type);
      $query->addExpression('MAX(nid)', 'max');
      $max_nid = $query->execute()->fetchField();

      // Ensure a node exists for the type.
      if (!$max_nid) {
        continue;
      }

      $r = rand(1, $max_nid);
      $content_id = db_select('node', 'n')
        ->fields('n', array('nid'))
        ->condition('type', $content_type)
        ->condition('nid', $r)
        ->range(0, 1)
        ->execute()
        ->fetchField();

      // We can't assume that every attempt will result in a listing because
      // we may have a node type with no nodes yet or a user with no lists.
      // Also, if a listing already exists, we count it, but it can only be in
      // the db once.
      if (flag_lists_do_flag($list, 'flag', $content_id, $account, TRUE)) {
        $count++;
      }
    }
    drupal_set_message(t('@listings listed.', array('@listings' => format_plural($count, '1 node', '@count nodes'))));
    if ($count < $form_state['values']['listings']) {
      drupal_set_message(t('Listings are generated randomly. Occassionally a listing will not be created if the random user has no lists or if the node type to be listed has no nodes.'));
    }
  }
}

function flag_lists_autocomplete_list_callback($string = "") {
  $matches = array();

  if ($string) {
    $lists = flag_lists_get_user_flags();
    foreach ($lists as $list) {
      if (stristr($list->title,$string) !== FALSE) {
        $matches[$list->title] = check_plain($list->title);
      }
    }
  }

  drupal_json_output($matches);
}
