<?php
/**
 * @file
 * Contains default views for the flag_lists module.
 */

/**
 * Implementation of hook_views_default_views().
 */
function flag_lists_views_default_views() {
  $view = new view;
  $view->name = 'flag_lists';
  $view->description = 'Flag lists';
  $view->tag = '';
  $view->view_php = '';
  $view->base_table = 'flag_lists_flags';
  $view->is_cacheable = FALSE;
  $view->api_version = 2;
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */
  $handler = $view->new_display('default', 'Defaults', 'default');
  $handler->override_option('fields', array(
    'title' => array(
      'label' => 'List',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'link_class' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'link_to_list' => 1,
      'exclude' => 0,
      'id' => 'title',
      'table' => 'flag_lists_flags',
      'field' => 'title',
      'relationship' => 'none',
    ),
    'name' => array(
      'label' => 'Owner',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'link_class' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'link_to_user' => 1,
      'overwrite_anonymous' => 0,
      'anonymous_text' => '',
      'exclude' => 0,
      'id' => 'name',
      'table' => 'users',
      'field' => 'name',
      'relationship' => 'none',
    ),
    'edit_list' => array(
      'label' => 'Operations',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'link_class' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'text' => 'edit',
      'exclude' => 0,
      'id' => 'edit_list',
      'table' => 'flag_lists_flags',
      'field' => 'edit_list',
      'relationship' => 'none',
    ),
    'delete_list' => array(
      'label' => 'Delete link',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'link_class' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'text' => '',
      'exclude' => 0,
      'id' => 'delete_list',
      'table' => 'flag_lists_flags',
      'field' => 'delete_list',
      'relationship' => 'none',
    ),
    'name_2' => array(
      'label' => 'Edit template',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'link_class' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 0,
        'ellipsis' => 0,
        'html' => 0,
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'link_to_template' => 1,
      'exclude' => 0,
      'link_to_list' => FALSE,
      'id' => 'name_2',
      'table' => 'flag',
      'field' => 'name',
      'relationship' => 'none',
    ),
    'type' => array(
      'label' => 'Template types',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'link_class' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'type' => 'separator',
      'separator' => ', ',
      'exclude' => 0,
      'id' => 'type',
      'table' => 'flag_lists_types',
      'field' => 'type',
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('filters', array(
    'title' => array(
      'operator' => 'contains',
      'value' => '',
      'group' => '0',
      'exposed' => TRUE,
      'expose' => array(
        'use_operator' => 0,
        'operator' => 'title_op',
        'identifier' => 'title',
        'label' => 'List title',
        'optional' => 1,
        'remember' => 1,
      ),
      'case' => 0,
      'id' => 'title',
      'table' => 'flag_lists_flags',
      'field' => 'title',
      'relationship' => 'none',
    ),
    'uid' => array(
      'operator' => 'in',
      'value' => '',
      'group' => '0',
      'exposed' => TRUE,
      'expose' => array(
        'use_operator' => 0,
        'operator' => 'uid_op',
        'identifier' => 'uid',
        'label' => 'Owner',
        'optional' => 1,
        'remember' => 1,
        'reduce' => 0,
      ),
      'id' => 'uid',
      'table' => 'flag_lists_flags',
      'field' => 'uid',
      'relationship' => 'none',
    ),
    'name' => array(
      'operator' => 'in',
      'value' => array(),
      'group' => '0',
      'exposed' => TRUE,
      'expose' => array(
        'use_operator' => 0,
        'operator' => 'name_op',
        'identifier' => 'name',
        'label' => 'Template name',
        'optional' => 1,
        'single' => 1,
        'remember' => 0,
        'reduce' => 0,
      ),
      'id' => 'name',
      'table' => 'flag',
      'field' => 'name',
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('access', array(
    'type' => 'perm',
    'perm' => 'administer flags',
  ));
  $handler->override_option('cache', array(
    'type' => 'none',
  ));
  $handler->override_option('items_per_page', 25);
  $handler->override_option('use_pager', '1');
  $handler->override_option('style_plugin', 'table');
  $handler->override_option('style_options', array(
    'grouping' => '',
    'override' => 1,
    'sticky' => 0,
    'order' => 'asc',
    'columns' => array(
      'title' => 'title',
      'name' => 'name',
      'edit_list' => 'edit_list',
      'delete_list' => 'edit_list',
      'name_2' => 'name_2',
    ),
    'info' => array(
      'title' => array(
        'sortable' => 1,
        'separator' => '',
      ),
      'name' => array(
        'sortable' => 1,
        'separator' => '',
      ),
      'edit_list' => array(
        'separator' => ' ',
      ),
      'delete_list' => array(
        'separator' => '',
      ),
      'name_2' => array(
        'sortable' => 0,
        'separator' => '',
      ),
    ),
    'default' => 'title',
  ));
  $views[$view->name] = $view;
  $view = new view;
  $view->name = 'flag_lists_content';
  $view->description = 'Flag lists listed content';
  $view->tag = '';
  $view->view_php = '';
  $view->base_table = 'node';
  $view->is_cacheable = FALSE;
  $view->api_version = 2;
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */
  $handler = $view->new_display('default', 'Defaults', 'default');
  $handler->override_option('relationships', array(
    'entity_id' => array(
      'label' => 'Listed content',
      'required' => 1,
      'id' => 'entity_id',
      'table' => 'flag_lists_content',
      'field' => 'entity_id',
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('fields', array(
    'title' => array(
      'label' => 'Node Title',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'link_class' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'link_to_node' => 1,
      'exclude' => 0,
      'id' => 'title',
      'table' => 'node',
      'field' => 'title',
      'relationship' => 'none',
    ),
    'title_1' => array(
      'label' => 'List title',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'link_class' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'link_to_list' => 1,
      'exclude' => 0,
      'id' => 'title_1',
      'table' => 'flag_lists_flags',
      'field' => 'title',
      'relationship' => 'none',
    ),
    // Daniel Frings: add description, period dates and distance
    'description' => array(
      'label' => 'List Description',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'link_class' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'link_to_list' => 0,
      'exclude' => 0,
      'id' => 'description',
      'table' => 'flag_lists_flags',
      'field' => 'description',
      'relationship' => 'none',
    ),
    'period_start' => array(
      'label' => 'Tour start date',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'link_class' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'link_to_list' => 0,
      'exclude' => 0,
      'id' => 'period_start',
      'table' => 'flag_lists_flags',
      'field' => 'period_start',
      'relationship' => 'none',
    ),
    'period_end' => array(
      'label' => 'Tour end date',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'link_class' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'link_to_list' => 0,
      'exclude' => 0,
      'id' => 'period_end',
      'table' => 'flag_lists_flags',
      'field' => 'period_end',
      'relationship' => 'none',
    ),
    'tour_distance' => array(
      'label' => 'Tour distance in KM',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'link_class' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'link_to_list' => 0,
      'exclude' => 0,
      'id' => 'tour_distance',
      'table' => 'flag_lists_flags',
      'field' => 'tour_distance',
      'relationship' => 'none',
    ),
    'name' => array(
      'label' => 'Name',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'link_class' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'link_to_user' => 1,
      'overwrite_anonymous' => 0,
      'anonymous_text' => '',
      'exclude' => 0,
      'id' => 'name',
      'table' => 'users',
      'field' => 'name',
      'relationship' => 'uid',
    ),
    'timestamp' => array(
      'label' => 'Time listed',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'link_class' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'date_format' => 'small',
      'custom_date_format' => '',
      'exclude' => 0,
      'id' => 'timestamp',
      'table' => 'flag_lists_content',
      'field' => 'timestamp',
      'relationship' => 'none',
    ),
    'weight' => array(
      'label' => 'List Item weighttt',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'link_class' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'link_to_list' => 0,
      'exclude' => 0,
      'id' => 'weight',
      'table' => 'flag_lists_content',
      'field' => 'weight',
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('filters', array(
    'status' => array(
      'operator' => '=',
      'value' => '1',
      'group' => '0',
      'exposed' => FALSE,
      'expose' => array(
        'operator' => FALSE,
        'label' => '',
      ),
      'id' => 'status',
      'table' => 'node',
      'field' => 'status',
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('access', array(
    'type' => 'perm',
    'perm' => 'view flag lists',
  ));
  $handler->override_option('cache', array(
    'type' => 'none',
  ));
  $handler->override_option('items_per_page', 25);
  $handler->override_option('use_pager', '1');
  $handler->override_option('style_plugin', 'table');
  $handler->override_option('style_options', array(
    'grouping' => '',
    'override' => 1,
    'sticky' => 0,
    'order' => 'desc',
    'columns' => array(
      'title' => 'title',
      'title_1' => 'title_1',
      'name' => 'name',
      'timestamp' => 'timestamp',
      'weight' => 'weight',

    ),
    'info' => array(
      'title' => array(
        'sortable' => 1,
        'separator' => '',
      ),
      'title_1' => array(
        'sortable' => 1,
        'separator' => '',
      ),
      'name' => array(
        'sortable' => 1,
        'separator' => '',
      ),
      'timestamp' => array(
        'sortable' => 1,
        'separator' => '',
      ),
      'weight' => array(
        'sortable' => 1,
        'separator' => '',
      ),
    ),
    'default' => 'timestamp',
  ));




  $views[$view->name] = $view;
  $view = new view;
  $view->name = 'flag_lists_user_lists';
  $view->description = 'Flag lists user lists';
  $view->tag = '';
  $view->view_php = '';
  $view->base_table = 'flag_lists_flags';
  $view->is_cacheable = FALSE;
  $view->api_version = 2;
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */
  $handler = $view->new_display('default', 'Defaults', 'default');
  $handler->override_option('fields', array(
    'title' => array(
      'label' => 'List',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'link_class' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'link_to_list' => 1,
      'exclude' => 0,
      'id' => 'title',
      'table' => 'flag_lists_flags',
      'field' => 'title',
      'relationship' => 'none',
    ),
    'edit_list' => array(
      'label' => 'Edit link',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'link_class' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'text' => 'Edit',
      'exclude' => 0,
      'id' => 'edit_list',
      'table' => 'flag_lists_flags',
      'field' => 'edit_list',
      'relationship' => 'none',
    ),
    'delete_list' => array(
      'label' => 'Delete link',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'link_class' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'text' => '',
      'exclude' => 0,
      'id' => 'delete_list',
      'table' => 'flag_lists_flags',
      'field' => 'delete_list',
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('arguments', array(
    'uid' => array(
      'default_action' => 'not found',
      'style_plugin' => 'default_summary',
      'style_options' => array(),
      'wildcard' => 'all',
      'wildcard_substitution' => 'All',
      'title' => '%1\'s lists',
      'breadcrumb' => '',
      'default_argument_type' => 'fixed',
      'default_argument' => '',
      'validate_type' => 'none',
      'validate_fail' => 'not found',
      'break_phrase' => 0,
      'not' => 0,
      'id' => 'uid',
      'table' => 'flag_lists_flags',
      'field' => 'uid',
      'validate_user_argument_type' => 'uid',
      'validate_user_roles' => array(
        '2' => 0,
      ),
      'relationship' => 'none',
      'default_options_div_prefix' => '',
      'default_argument_fixed' => '',
      'default_argument_user' => 0,
      'default_argument_php' => '',
      'validate_argument_node_type' => array(
        'page' => 0,
        'story' => 0,
      ),
      'validate_argument_node_access' => 0,
      'validate_argument_nid_type' => 'nid',
      'validate_argument_vocabulary' => array(),
      'validate_argument_type' => 'tid',
      'validate_argument_transform' => 0,
      'validate_user_restrict_roles' => 0,
      'validate_argument_node_flag_name' => '*relationship*',
      'validate_argument_node_flag_test' => 'flaggable',
      'validate_argument_node_flag_id_type' => 'id',
      'validate_argument_user_flag_name' => '*relationship*',
      'validate_argument_user_flag_test' => 'flaggable',
      'validate_argument_user_flag_id_type' => 'id',
      'validate_argument_php' => '',
    ),
  ));
  $handler->override_option('access', array(
    'type' => 'perm',
    'perm' => 'view flag lists',
  ));
  $handler->override_option('cache', array(
    'type' => 'none',
  ));
  $handler->override_option('items_per_page', 25);
  $handler->override_option('use_pager', '1');
  $handler->override_option('style_plugin', 'table');
  $handler->override_option('style_options', array(
    'grouping' => '',
    'override' => 1,
    'sticky' => 0,
    'order' => 'asc',
    'columns' => array(
      'title' => 'title',
      'name' => 'name',
    ),
    'info' => array(
      'title' => array(
        'sortable' => 1,
        'separator' => '',
      ),
      'name' => array(
        'sortable' => 1,
        'separator' => '',
      ),
    ),
    'default' => 'title',
  ));

  //
  // $views[$view->name] = $view;
  // $view = new view;
  // $view->name = 'flag_lists_user_list';
  // $view->description = 'Flag lists - one of a user\'s lists';
  // $view->tag = '';
  // $view->view_php = '';
  // $view->base_table = 'node';
  // $view->is_cacheable = FALSE;
  // $view->api_version = 2;
  // $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */
  // $handler = $view->new_display('default', 'Defaults', 'default');
  // $handler->override_option('fields', array(
  //   'title' => array(
  //     'label' => '',
  //     'alter' => array(
  //       'alter_text' => 0,
  //       'text' => '',
  //       'make_link' => 0,
  //       'path' => '',
  //       'link_class' => '',
  //       'alt' => '',
  //       'prefix' => '',
  //       'suffix' => '',
  //       'target' => '',
  //       'help' => '',
  //       'trim' => 0,
  //       'max_length' => '',
  //       'word_boundary' => 1,
  //       'ellipsis' => 1,
  //       'html' => 0,
  //       'strip_tags' => 0,
  //     ),
  //     'empty' => '',
  //     'hide_empty' => 0,
  //     'empty_zero' => 0,
  //     'link_to_node' => 1,
  //     'exclude' => 0,
  //     'id' => 'title',
  //     'table' => 'node',
  //     'field' => 'title',
  //     'relationship' => 'none',
  //   ),
  // ));
  // $handler->override_option('sorts', array(
  //   'timestamp' => array(
  //     'order' => 'DESC',
  //     'id' => 'timestamp',
  //     'table' => 'flag_lists_content',
  //     'field' => 'timestamp',
  //     'relationship' => 'none',
  //   ),
  //   'weight' => array(
  //     'order' => 'DESC',
  //     'id' => 'weight',
  //     'table' => 'flag_lists_content',
  //     'field' => 'weight',
  //     'relationship' => 'none',
  //   ),
  // ));
  // $handler->override_option('arguments', array(
  //   'fid' => array(
  //     'default_action' => 'not found',
  //     'style_plugin' => 'default_summary',
  //     'style_options' => array(),
  //     'wildcard' => 'all',
  //     'wildcard_substitution' => 'All',
  //     'title' => '%1',
  //     'breadcrumb' => '',
  //     'default_argument_type' => 'fixed',
  //     'default_argument' => '',
  //     'validate_type' => 'none',
  //     'validate_fail' => 'not found',
  //     'break_phrase' => 0,
  //     'not' => 0,
  //     'id' => 'fid',
  //     'table' => 'flag_lists_flags',
  //     'field' => 'fid',
  //     'validate_user_argument_type' => 'uid',
  //     'validate_user_roles' => array(
  //       '2' => 0,
  //       '3' => 0,
  //       '4' => 0,
  //     ),
  //     'relationship' => 'none',
  //     'default_options_div_prefix' => '',
  //     'default_argument_fixed' => '',
  //     'default_argument_user' => 0,
  //     'default_argument_image_size' => '_original',
  //     'default_argument_php' => '',
  //     'validate_argument_node_type' => array(
  //       'image' => 0,
  //       'club' => 0,
  //       'club_topic' => 0,
  //       'page' => 0,
  //       'profile' => 0,
  //       'story' => 0,
  //       'vehicle' => 0,
  //     ),
  //     'validate_argument_node_access' => 0,
  //     'validate_argument_nid_type' => 'nid',
  //     'validate_argument_vocabulary' => array(
  //       '1' => 0,
  //       '3' => 0,
  //     ),
  //     'validate_argument_type' => 'tid',
  //     'validate_argument_transform' => 0,
  //     'validate_user_restrict_roles' => 0,
  //     'validate_argument_node_flag_name' => '*relationship*',
  //     'validate_argument_node_flag_test' => 'flaggable',
  //     'validate_argument_node_flag_id_type' => 'id',
  //     'validate_argument_user_flag_name' => '*relationship*',
  //     'validate_argument_user_flag_test' => 'flaggable',
  //     'validate_argument_user_flag_id_type' => 'id',
  //     'image_size' => array(
  //       '_original' => '_original',
  //       'thumbnail' => 'thumbnail',
  //       'preview' => 'preview',
  //       'home' => 'home',
  //       'expanded' => 'expanded',
  //       'block_icon' => 'block_icon',
  //       'club_grid' => 'club_grid',
  //       'full' => 'full',
  //     ),
  //     'validate_argument_is_member' => 'OG_VIEWS_DO_NOT_VALIDATE_MEMBERSHIP',
  //     'validate_argument_group_node_type' => array(
  //       'club' => 0,
  //     ),
  //     'validate_argument_php' => '',
  //     'override' => array(
  //       'button' => 'Override',
  //     ),
  //   ),
  // ));
  // $handler->override_option('filters', array(
  //   'status' => array(
  //     'operator' => '=',
  //     'value' => '1',
  //     'group' => '0',
  //     'exposed' => FALSE,
  //     'expose' => array(
  //       'operator' => FALSE,
  //       'label' => '',
  //     ),
  //     'id' => 'status',
  //     'table' => 'node',
  //     'field' => 'status',
  //     'relationship' => 'none',
  //   ),
  // ));
  // $handler->override_option('access', array(
  //   'type' => 'none',
  // ));
  // $handler->override_option('cache', array(
  //   'type' => 'none',
  // ));
  // $handler = $view->new_display('page', 'Page', 'page_1');
  // $handler->override_option('path', 'flag/lists/%');
  // $handler->override_option('menu', array(
  //   'type' => 'none',
  //   'title' => '',
  //   'description' => '',
  //   'weight' => 0,
  //   'name' => 'navigation',
  // ));
  // $handler->override_option('tab_options', array(
  //   'type' => 'none',
  //   'title' => '',
  //   'description' => '',
  //   'weight' => 0,
  //   'name' => 'navigation',
  // ));
  // $views[$view->name] = $view;
  //
  //


  /* Daniel Frings Add custom views*/

  // VIEW: touren_bereich_ansicht_is_in_tour --  show first image from tour
  $view = new view();
  $view->name = 'touren_bereich_ansicht_is_in_tour';
  $view->description = 'Touren Bereich: Ansicht is in Tour ';
  $view->tag = '';
  $view->base_table = 'node';
  $view->human_name = 'Touren Bereich: Ansicht is in Tour';
  $view->core = 0;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Defaults */
  $handler = $view->new_display('default', 'Defaults', 'default');
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['reset_button_label'] = 'Zurücksetzen';
  $handler->display->display_options['exposed_form']['options']['exposed_sorts_label'] = 'Sortierung';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'views_delimited_list';
  $handler->display->display_options['style_options']['long_count'] = '3';
  $handler->display->display_options['style_options']['separator_two'] = 'delimiter';
  $handler->display->display_options['style_options']['separator_long'] = 'delimiter';
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['row_options']['default_field_elements'] = FALSE;
  /* Feld: Flag lists: fid */
  $handler->display->display_options['fields']['fid']['id'] = 'fid';
  $handler->display->display_options['fields']['fid']['table'] = 'flag_lists_flags';
  $handler->display->display_options['fields']['fid']['field'] = 'fid';
  $handler->display->display_options['fields']['fid']['label'] = '';
  $handler->display->display_options['fields']['fid']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['fid']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['fid']['empty'] = 'NULL';
  $handler->display->display_options['fields']['fid']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['fid']['link_to_list'] = 0;
  /* Feld: Inhalt: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['label'] = '';
  $handler->display->display_options['fields']['nid']['exclude'] = TRUE;
  $handler->display->display_options['fields']['nid']['element_label_colon'] = FALSE;
  /* Contextual filter: Inhalt: Nid */
  $handler->display->display_options['arguments']['nid']['id'] = 'nid';
  $handler->display->display_options['arguments']['nid']['table'] = 'node';
  $handler->display->display_options['arguments']['nid']['field'] = 'nid';
  $handler->display->display_options['arguments']['nid']['exception']['title'] = 'Alle';
  $handler->display->display_options['arguments']['nid']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['nid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['nid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['nid']['summary_options']['items_per_page'] = '25';

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page_1');
  $handler->display->display_options['path'] = 'tour_node_list';
  $translatables['touren_bereich_ansicht_is_in_tour'] = array(
    t('Defaults'),
    t('more'),
    t('Apply'),
    t('Zurücksetzen'),
    t('Sortierung'),
    t('Asc'),
    t('Desc'),
    t('NULL'),
    t('Alle'),
    t('Page'),
  );


// VIEW: touren_bereich_subview_f_r_erstes_bild_der_tour --  show first image from tour Portal
$view = new view();
$view->name = 'touren_bereich_subview_f_r_erstes_bild_der_tour';
$view->description = 'show first image from tour ';
$view->tag = '';
$view->base_table = 'node';
$view->human_name = 'Touren Bereich: Subview für erstes Bild der Tour';
$view->core = 0;
$view->api_version = '3.0';
$view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

/* Display: Defaults */
$handler = $view->new_display('default', 'Defaults', 'default');
$handler->display->display_options['use_more_always'] = FALSE;
$handler->display->display_options['access']['type'] = 'none';
$handler->display->display_options['cache']['type'] = 'none';
$handler->display->display_options['query']['type'] = 'views_query';
$handler->display->display_options['exposed_form']['type'] = 'basic';
$handler->display->display_options['exposed_form']['options']['reset_button_label'] = 'Zurücksetzen';
$handler->display->display_options['exposed_form']['options']['exposed_sorts_label'] = 'Sortierung';
$handler->display->display_options['pager']['type'] = 'some';
$handler->display->display_options['pager']['options']['items_per_page'] = '1';
$handler->display->display_options['pager']['options']['offset'] = '0';
$handler->display->display_options['style_plugin'] = 'default';
$handler->display->display_options['row_plugin'] = 'fields';
/* Feld: Inhalt: Bild */
$handler->display->display_options['fields']['field_bild']['id'] = 'field_bild';
$handler->display->display_options['fields']['field_bild']['table'] = 'field_data_field_bild';
$handler->display->display_options['fields']['field_bild']['field'] = 'field_bild';
$handler->display->display_options['fields']['field_bild']['label'] = '';
$handler->display->display_options['fields']['field_bild']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['field_bild']['click_sort_column'] = 'fid';
$handler->display->display_options['fields']['field_bild']['settings'] = array(
  'image_style' => 'fh_grid_view',
  'image_link' => '',
);
/* Sort criterion: Flag lists: Time listed */
$handler->display->display_options['sorts']['timestamp']['id'] = 'timestamp';
$handler->display->display_options['sorts']['timestamp']['table'] = 'flag_lists_content';
$handler->display->display_options['sorts']['timestamp']['field'] = 'timestamp';
$handler->display->display_options['sorts']['timestamp']['order'] = 'DESC';
/* Contextual filter: Flag lists: fid */
$handler->display->display_options['arguments']['fid']['id'] = 'fid';
$handler->display->display_options['arguments']['fid']['table'] = 'flag_lists_flags';
$handler->display->display_options['arguments']['fid']['field'] = 'fid';
$handler->display->display_options['arguments']['fid']['default_action'] = 'not found';
$handler->display->display_options['arguments']['fid']['exception']['title_enable'] = TRUE;
$handler->display->display_options['arguments']['fid']['title_enable'] = TRUE;
$handler->display->display_options['arguments']['fid']['title'] = '%1';
$handler->display->display_options['arguments']['fid']['default_argument_type'] = 'fixed';
$handler->display->display_options['arguments']['fid']['summary']['format'] = 'default_summary';
$handler->display->display_options['arguments']['fid']['specify_validation'] = TRUE;
/* Filter criterion: Inhalt: Veröffentlicht */
$handler->display->display_options['filters']['status']['id'] = 'status';
$handler->display->display_options['filters']['status']['table'] = 'node';
$handler->display->display_options['filters']['status']['field'] = 'status';
$handler->display->display_options['filters']['status']['value'] = '1';
$handler->display->display_options['filters']['status']['group'] = '0';
$handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;

/* Display: Page */
$handler = $view->new_display('page', 'Page', 'page_1');
$handler->display->display_options['path'] = 'tour_picture';
$translatables['touren_bereich_subview_f_r_erstes_bild_der_tour'] = array(
  t('Defaults'),
  t('more'),
  t('Apply'),
  t('Zurücksetzen'),
  t('Sortierung'),
  t('Asc'),
  t('Desc'),
  t('All'),
  t('%1'),
  t('Page'),
);




  // VIEW: rest_list_touren --  List all touren for mobile Device
  $view = new view();
  $view->name = 'rest_list_touren';
  $view->description = 'List all touren for mobile Device';
  $view->tag = 'default';
  $view->base_table = 'flag_lists_flags';
  $view->human_name = 'Touren Bereich: Auflistung der Touren für REST API';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Meine Touren';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['reset_button_label'] = 'Zurücksetzen';
  $handler->display->display_options['exposed_form']['options']['exposed_sorts_label'] = 'Sortierung';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'title' => 'title',
    'description' => 'description',
    'tour_distance' => 'tour_distance',
    'period_end' => 'period_end',
    'period_start' => 'period_start',
    'fid' => 'fid',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'title' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'description' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'tour_distance' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'period_end' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'period_start' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'fid' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  /* Feld: Flag lists: fid */
  $handler->display->display_options['fields']['fid']['id'] = 'fid';
  $handler->display->display_options['fields']['fid']['table'] = 'flag_lists_flags';
  $handler->display->display_options['fields']['fid']['field'] = 'fid';
  $handler->display->display_options['fields']['fid']['label'] = 'tour_id';
  $handler->display->display_options['fields']['fid']['link_to_list'] = 0;
  /* Feld: Flag lists: List title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'flag_lists_flags';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['link_to_list'] = 0;
  /* Feld: Flag lists: List description */
  $handler->display->display_options['fields']['description']['id'] = 'description';
  $handler->display->display_options['fields']['description']['table'] = 'flag_lists_flags';
  $handler->display->display_options['fields']['description']['field'] = 'description';
  $handler->display->display_options['fields']['description']['label'] = '';
  $handler->display->display_options['fields']['description']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['description']['link_to_list'] = 0;
  /* Feld: Flag lists: Tour distance in KM */
  $handler->display->display_options['fields']['tour_distance']['id'] = 'tour_distance';
  $handler->display->display_options['fields']['tour_distance']['table'] = 'flag_lists_flags';
  $handler->display->display_options['fields']['tour_distance']['field'] = 'tour_distance';
  $handler->display->display_options['fields']['tour_distance']['label'] = 'distance';
  $handler->display->display_options['fields']['tour_distance']['link_to_list'] = 0;
  /* Feld: Flag lists: Tour end date */
  $handler->display->display_options['fields']['period_end']['id'] = 'period_end';
  $handler->display->display_options['fields']['period_end']['table'] = 'flag_lists_flags';
  $handler->display->display_options['fields']['period_end']['field'] = 'period_end';
  $handler->display->display_options['fields']['period_end']['label'] = 'tour_end_date';
  $handler->display->display_options['fields']['period_end']['link_to_list'] = 0;
  /* Feld: Flag lists: Tour start date */
  $handler->display->display_options['fields']['period_start']['id'] = 'period_start';
  $handler->display->display_options['fields']['period_start']['table'] = 'flag_lists_flags';
  $handler->display->display_options['fields']['period_start']['field'] = 'period_start';
  $handler->display->display_options['fields']['period_start']['label'] = 'tour_start_date';
  $handler->display->display_options['fields']['period_start']['link_to_list'] = 0;
  /* Feld: Benutzer: Uid */
  $handler->display->display_options['fields']['uid']['id'] = 'uid';
  $handler->display->display_options['fields']['uid']['table'] = 'users';
  $handler->display->display_options['fields']['uid']['field'] = 'uid';
  $handler->display->display_options['fields']['uid']['label'] = 'user_id';
  $handler->display->display_options['fields']['uid']['link_to_user'] = FALSE;
  /* Feld: Benutzer: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'users';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['label'] = 'name';
  $handler->display->display_options['fields']['name']['link_to_user'] = FALSE;
  /* Contextual filter: Flag lists: fid */
  $handler->display->display_options['arguments']['fid']['id'] = 'fid';
  $handler->display->display_options['arguments']['fid']['table'] = 'flag_lists_flags';
  $handler->display->display_options['arguments']['fid']['field'] = 'fid';
  $handler->display->display_options['arguments']['fid']['default_action'] = 'default';
  $handler->display->display_options['arguments']['fid']['exception']['title'] = 'Alle';
  $handler->display->display_options['arguments']['fid']['default_argument_type'] = 'query';
  $handler->display->display_options['arguments']['fid']['default_argument_options']['parameter'] = 'tour_id';
  $handler->display->display_options['arguments']['fid']['default_argument_options']['default_value'] = 'all';
  $handler->display->display_options['arguments']['fid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['fid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['fid']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['fid']['break_phrase'] = TRUE;

  /* Display: Services */
  $handler = $view->new_display('services', 'Services', 'services_1');
  $handler->display->display_options['path'] = 'list_tours';
  $translatables['rest_list_touren'] = array(
    t('Master'),
    t('Meine Touren'),
    t('more'),
    t('Apply'),
    t('Zurücksetzen'),
    t('Sortierung'),
    t('Asc'),
    t('Desc'),
    t('tour_id'),
    t('distance'),
    t('tour_end_date'),
    t('tour_start_date'),
    t('user_id'),
    t('name'),
    t('Alle'),
    t('Services'),
  );



  // VIEW: meine_touren --  Auflistung der Touren im Portal
  $view = new view();
  $view->name = 'meine_touren';
  $view->description = 'Auflistung der Touren im Portal';
  $view->tag = 'default';
  $view->base_table = 'flag_lists_flags';
  $view->human_name = 'Touren Bereich: Auflistung der Touren im Portal';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Meine Touren';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['reset_button_label'] = 'Zurücksetzen';
  $handler->display->display_options['exposed_form']['options']['exposed_sorts_label'] = 'Sortierung';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'list';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Kopfbereich: Global: Text area */
  $handler->display->display_options['header']['area']['id'] = 'area';
  $handler->display->display_options['header']['area']['table'] = 'views';
  $handler->display->display_options['header']['area']['field'] = 'area';
  $handler->display->display_options['header']['area']['content'] = '<h4>Meine Touren</h4>';
  $handler->display->display_options['header']['area']['format'] = 'full_html';
  /* Feld: Flag lists: fid */
  $handler->display->display_options['fields']['fid']['id'] = 'fid';
  $handler->display->display_options['fields']['fid']['table'] = 'flag_lists_flags';
  $handler->display->display_options['fields']['fid']['field'] = 'fid';
  $handler->display->display_options['fields']['fid']['exclude'] = TRUE;
  $handler->display->display_options['fields']['fid']['link_to_list'] = 0;
  /* Feld: Flag lists: List title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'flag_lists_flags';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['link_to_list'] = 1;
  /* Feld: Global: Ansicht */
  $handler->display->display_options['fields']['view']['id'] = 'view';
  $handler->display->display_options['fields']['view']['table'] = 'views';
  $handler->display->display_options['fields']['view']['field'] = 'view';
  $handler->display->display_options['fields']['view']['label'] = '';
  $handler->display->display_options['fields']['view']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['view']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['view']['view'] = 'touren_bereich_subview_f_r_erstes_bild_der_tour';
  $handler->display->display_options['fields']['view']['display'] = 'page_1';
  $handler->display->display_options['fields']['view']['arguments'] = '[!fid]';
  /* Feld: Flag lists: List description */
  $handler->display->display_options['fields']['description']['id'] = 'description';
  $handler->display->display_options['fields']['description']['table'] = 'flag_lists_flags';
  $handler->display->display_options['fields']['description']['field'] = 'description';
  $handler->display->display_options['fields']['description']['label'] = '';
  $handler->display->display_options['fields']['description']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['description']['link_to_list'] = 0;
  /* Feld: Flag lists: Tour distance in KM */
  $handler->display->display_options['fields']['tour_distance']['id'] = 'tour_distance';
  $handler->display->display_options['fields']['tour_distance']['table'] = 'flag_lists_flags';
  $handler->display->display_options['fields']['tour_distance']['field'] = 'tour_distance';
  $handler->display->display_options['fields']['tour_distance']['label'] = 'Wegstrecke in Metern';
  $handler->display->display_options['fields']['tour_distance']['link_to_list'] = 0;
  /* Feld: Flag lists: Tour start date */
  $handler->display->display_options['fields']['period_start']['id'] = 'period_start';
  $handler->display->display_options['fields']['period_start']['table'] = 'flag_lists_flags';
  $handler->display->display_options['fields']['period_start']['field'] = 'period_start';
  $handler->display->display_options['fields']['period_start']['label'] = 'Anfangsjahr';
  $handler->display->display_options['fields']['period_start']['link_to_list'] = 0;
  /* Feld: Flag lists: Tour end date */
  $handler->display->display_options['fields']['period_end']['id'] = 'period_end';
  $handler->display->display_options['fields']['period_end']['table'] = 'flag_lists_flags';
  $handler->display->display_options['fields']['period_end']['field'] = 'period_end';
  $handler->display->display_options['fields']['period_end']['label'] = 'Endjahr';
  $handler->display->display_options['fields']['period_end']['link_to_list'] = 0;
  /* Feld: Flag lists: Edit link */
  $handler->display->display_options['fields']['edit_list']['id'] = 'edit_list';
  $handler->display->display_options['fields']['edit_list']['table'] = 'flag_lists_flags';
  $handler->display->display_options['fields']['edit_list']['field'] = 'edit_list';
  $handler->display->display_options['fields']['edit_list']['label'] = '';
  $handler->display->display_options['fields']['edit_list']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['edit_list']['text'] = 'Bearbeiten';
  /* Feld: Flag lists: Delete link */
  $handler->display->display_options['fields']['delete_list']['id'] = 'delete_list';
  $handler->display->display_options['fields']['delete_list']['table'] = 'flag_lists_flags';
  $handler->display->display_options['fields']['delete_list']['field'] = 'delete_list';
  $handler->display->display_options['fields']['delete_list']['label'] = '';
  $handler->display->display_options['fields']['delete_list']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['delete_list']['text'] = 'Tour Löschen';
  /* Contextual filter: Benutzer: Uid */
  $handler->display->display_options['arguments']['uid']['id'] = 'uid';
  $handler->display->display_options['arguments']['uid']['table'] = 'users';
  $handler->display->display_options['arguments']['uid']['field'] = 'uid';
  $handler->display->display_options['arguments']['uid']['default_action'] = 'default';
  $handler->display->display_options['arguments']['uid']['exception']['title'] = 'Alle';
  $handler->display->display_options['arguments']['uid']['default_argument_type'] = 'current_user';
  $handler->display->display_options['arguments']['uid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['uid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['uid']['summary_options']['items_per_page'] = '25';

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'user/touren';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'Touren';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['name'] = 'user-menu';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;
  $translatables['meine_touren'] = array(
    t('Master'),
    t('Meine Touren'),
    t('more'),
    t('Apply'),
    t('Zurücksetzen'),
    t('Sortierung'),
    t('Asc'),
    t('Desc'),
    t('<h4>Meine Touren</h4>'),
    t('fid'),
    t('Wegstrecke in Metern'),
    t('Anfangsjahr'),
    t('Endjahr'),
    t('Bearbeiten'),
    t('Tour Löschen'),
    t('Alle'),
    t('Page'),
  );


  // VIEW: rest_list_touren_content --  List Touren Content with argumend FID
  $view = new view();
  $view->name = 'rest_list_touren_content';
  $view->description = 'List Touren Content with argumend FID';
  $view->tag = '';
  $view->base_table = 'node';
  $view->human_name = 'Touren Bereich: Auflistung des Touren Inhalts für REST API';
  $view->core = 0;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Defaults */
  $handler = $view->new_display('default', 'Defaults', 'default');
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['reset_button_label'] = 'Zurücksetzen';
  $handler->display->display_options['exposed_form']['options']['exposed_sorts_label'] = 'Sortierung';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['style_plugin'] = 'list';
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['row_options']['inline'] = array(
    'description' => 'description',
  );
  /* Feld: Inhalt: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['label'] = 'nid';
  /* Feld: Flag lists: fid */
  $handler->display->display_options['fields']['fid']['id'] = 'fid';
  $handler->display->display_options['fields']['fid']['table'] = 'flag_lists_flags';
  $handler->display->display_options['fields']['fid']['field'] = 'fid';
  $handler->display->display_options['fields']['fid']['label'] = 'tour_id';
  $handler->display->display_options['fields']['fid']['link_to_list'] = 0;
  /* Feld: Inhalt: Titel */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['link_to_node'] = FALSE;
  /* Feld: Inhalt: Bild */
  $handler->display->display_options['fields']['field_bild']['id'] = 'field_bild';
  $handler->display->display_options['fields']['field_bild']['table'] = 'field_data_field_bild';
  $handler->display->display_options['fields']['field_bild']['field'] = 'field_bild';
  $handler->display->display_options['fields']['field_bild']['label'] = '';
  $handler->display->display_options['fields']['field_bild']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_bild']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_bild']['type'] = 'image_url';
  $handler->display->display_options['fields']['field_bild']['settings'] = array(
    'url_type' => '0',
    'image_style' => 'fh_grid_view',
    'image_link' => '',
  );
  /* Feld: Inhalt: Jahr */
  $handler->display->display_options['fields']['field_jahr']['id'] = 'field_jahr';
  $handler->display->display_options['fields']['field_jahr']['table'] = 'field_data_field_jahr';
  $handler->display->display_options['fields']['field_jahr']['field'] = 'field_jahr';
  $handler->display->display_options['fields']['field_jahr']['label'] = 'jahr';
  $handler->display->display_options['fields']['field_jahr']['settings'] = array(
    'thousand_separator' => '',
    'prefix_suffix' => 1,
  );
  /* Sort criterion: Flag lists: List items weight */
  $handler->display->display_options['sorts']['weight']['id'] = 'weight';
  $handler->display->display_options['sorts']['weight']['table'] = 'flag_lists_content';
  $handler->display->display_options['sorts']['weight']['field'] = 'weight';
  /* Sort criterion: Flag lists: Time listed */
  $handler->display->display_options['sorts']['timestamp']['id'] = 'timestamp';
  $handler->display->display_options['sorts']['timestamp']['table'] = 'flag_lists_content';
  $handler->display->display_options['sorts']['timestamp']['field'] = 'timestamp';
  /* Filter criterion: Inhalt: Veröffentlicht */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = '1';
  $handler->display->display_options['filters']['status']['group'] = '0';
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Flag lists: fid */
  $handler->display->display_options['filters']['fid']['id'] = 'fid';
  $handler->display->display_options['filters']['fid']['table'] = 'flag_lists_flags';
  $handler->display->display_options['filters']['fid']['field'] = 'fid';
  $handler->display->display_options['filters']['fid']['exposed'] = TRUE;
  $handler->display->display_options['filters']['fid']['expose']['operator_id'] = 'fid_op';
  $handler->display->display_options['filters']['fid']['expose']['label'] = 'tour_id';
  $handler->display->display_options['filters']['fid']['expose']['operator'] = 'fid_op';
  $handler->display->display_options['filters']['fid']['expose']['identifier'] = 'tour_id';
  $handler->display->display_options['filters']['fid']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    4 => 0,
    3 => 0,
  );

  /* Display: Services */
  $handler = $view->new_display('services', 'Services', 'services_1');
  $handler->display->display_options['path'] = 'list_tour_content';
  $translatables['rest_list_touren_content'] = array(
    t('Defaults'),
    t('more'),
    t('Apply'),
    t('Zurücksetzen'),
    t('Sortierung'),
    t('Asc'),
    t('Desc'),
    t('nid'),
    t('tour_id'),
    t('jahr'),
    t('Services'),
  );



  // VIEW: flag_lists_user_list --  List Touren Content PORTAL
  $view = new view();
  $view->name = 'flag_lists_user_list';
  $view->description = 'List Touren Content PORTAL';
  $view->tag = '';
  $view->base_table = 'node';
  $view->human_name = 'Touren Bereich: Auflistung des Touren Inhalts PORTAL';
  $view->core = 0;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Defaults */
  $handler = $view->new_display('default', 'Defaults', 'default');
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['reset_button_label'] = 'Zurücksetzen';
  $handler->display->display_options['exposed_form']['options']['exposed_sorts_label'] = 'Sortierung';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['style_plugin'] = 'list';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Kopfbereich: Global: Text area */
  $handler->display->display_options['header']['area']['id'] = 'area';
  $handler->display->display_options['header']['area']['table'] = 'views';
  $handler->display->display_options['header']['area']['field'] = 'area';
  $handler->display->display_options['header']['area']['content'] = '<h4>Meine Tour: [title_1] | [period_start] - [period_end] | [tour_distance] M</h4>
  <a href="/de/user/touren">Zurück zu meinen Touren</a> | [edit_list]
  <p>[description]</p>
  ';
  $handler->display->display_options['header']['area']['format'] = 'full_html';
  $handler->display->display_options['header']['area']['tokenize'] = TRUE;
  /* Feld: Inhalt: Titel */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  /* Feld: Inhalt: Jahr */
  $handler->display->display_options['fields']['field_jahr']['id'] = 'field_jahr';
  $handler->display->display_options['fields']['field_jahr']['table'] = 'field_data_field_jahr';
  $handler->display->display_options['fields']['field_jahr']['field'] = 'field_jahr';
  $handler->display->display_options['fields']['field_jahr']['label'] = '';
  $handler->display->display_options['fields']['field_jahr']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_jahr']['alter']['text'] = ' | [field_jahr]';
  $handler->display->display_options['fields']['field_jahr']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_jahr']['settings'] = array(
    'thousand_separator' => '',
    'prefix_suffix' => 1,
  );
  /* Feld: Flag lists: List description */
  $handler->display->display_options['fields']['description']['id'] = 'description';
  $handler->display->display_options['fields']['description']['table'] = 'flag_lists_flags';
  $handler->display->display_options['fields']['description']['field'] = 'description';
  $handler->display->display_options['fields']['description']['label'] = '';
  $handler->display->display_options['fields']['description']['exclude'] = TRUE;
  $handler->display->display_options['fields']['description']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['description']['link_to_list'] = 0;
  /* Feld: Flag lists: Tour distance in KM */
  $handler->display->display_options['fields']['tour_distance']['id'] = 'tour_distance';
  $handler->display->display_options['fields']['tour_distance']['table'] = 'flag_lists_flags';
  $handler->display->display_options['fields']['tour_distance']['field'] = 'tour_distance';
  $handler->display->display_options['fields']['tour_distance']['label'] = '';
  $handler->display->display_options['fields']['tour_distance']['exclude'] = TRUE;
  $handler->display->display_options['fields']['tour_distance']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['tour_distance']['link_to_list'] = 0;
  /* Feld: Flag lists: Tour end date */
  $handler->display->display_options['fields']['period_end']['id'] = 'period_end';
  $handler->display->display_options['fields']['period_end']['table'] = 'flag_lists_flags';
  $handler->display->display_options['fields']['period_end']['field'] = 'period_end';
  $handler->display->display_options['fields']['period_end']['label'] = '';
  $handler->display->display_options['fields']['period_end']['exclude'] = TRUE;
  $handler->display->display_options['fields']['period_end']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['period_end']['link_to_list'] = 0;
  /* Feld: Flag lists: Tour start date */
  $handler->display->display_options['fields']['period_start']['id'] = 'period_start';
  $handler->display->display_options['fields']['period_start']['table'] = 'flag_lists_flags';
  $handler->display->display_options['fields']['period_start']['field'] = 'period_start';
  $handler->display->display_options['fields']['period_start']['label'] = '';
  $handler->display->display_options['fields']['period_start']['exclude'] = TRUE;
  $handler->display->display_options['fields']['period_start']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['period_start']['link_to_list'] = 0;
  /* Feld: Inhalt: Bild */
  $handler->display->display_options['fields']['field_bild']['id'] = 'field_bild';
  $handler->display->display_options['fields']['field_bild']['table'] = 'field_data_field_bild';
  $handler->display->display_options['fields']['field_bild']['field'] = 'field_bild';
  $handler->display->display_options['fields']['field_bild']['label'] = '';
  $handler->display->display_options['fields']['field_bild']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_bild']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_bild']['settings'] = array(
    'image_style' => 'fh_grid_view',
    'image_link' => 'content',
  );
  /* Feld: Flag lists: Edit link */
  $handler->display->display_options['fields']['edit_list']['id'] = 'edit_list';
  $handler->display->display_options['fields']['edit_list']['table'] = 'flag_lists_flags';
  $handler->display->display_options['fields']['edit_list']['field'] = 'edit_list';
  $handler->display->display_options['fields']['edit_list']['label'] = '';
  $handler->display->display_options['fields']['edit_list']['exclude'] = TRUE;
  $handler->display->display_options['fields']['edit_list']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['edit_list']['text'] = 'Tour Bearbeiten';
  /* Feld: Flag lists: List title */
  $handler->display->display_options['fields']['title_1']['id'] = 'title_1';
  $handler->display->display_options['fields']['title_1']['table'] = 'flag_lists_flags';
  $handler->display->display_options['fields']['title_1']['field'] = 'title';
  $handler->display->display_options['fields']['title_1']['label'] = '';
  $handler->display->display_options['fields']['title_1']['exclude'] = TRUE;
  $handler->display->display_options['fields']['title_1']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title_1']['link_to_list'] = 0;
  /* Feld: Flag lists: Time listed */
  $handler->display->display_options['fields']['timestamp']['id'] = 'timestamp';
  $handler->display->display_options['fields']['timestamp']['table'] = 'flag_lists_content';
  $handler->display->display_options['fields']['timestamp']['field'] = 'timestamp';
  $handler->display->display_options['fields']['timestamp']['date_format'] = 'long';
  $handler->display->display_options['fields']['timestamp']['second_date_format'] = 'long';
  /* Feld: Flag lists: List items weight */
  $handler->display->display_options['fields']['weight']['id'] = 'weight';
  $handler->display->display_options['fields']['weight']['table'] = 'flag_lists_content';
  $handler->display->display_options['fields']['weight']['field'] = 'weight';
  /* Sort criterion: Flag lists: List items weight */
  $handler->display->display_options['sorts']['weight']['id'] = 'weight';
  $handler->display->display_options['sorts']['weight']['table'] = 'flag_lists_content';
  $handler->display->display_options['sorts']['weight']['field'] = 'weight';
  /* Sort criterion: Flag lists: Time listed */
  $handler->display->display_options['sorts']['timestamp']['id'] = 'timestamp';
  $handler->display->display_options['sorts']['timestamp']['table'] = 'flag_lists_content';
  $handler->display->display_options['sorts']['timestamp']['field'] = 'timestamp';
  /* Contextual filter: Flag lists: fid */
  $handler->display->display_options['arguments']['fid']['id'] = 'fid';
  $handler->display->display_options['arguments']['fid']['table'] = 'flag_lists_flags';
  $handler->display->display_options['arguments']['fid']['field'] = 'fid';
  $handler->display->display_options['arguments']['fid']['default_action'] = 'not found';
  $handler->display->display_options['arguments']['fid']['exception']['title_enable'] = TRUE;
  $handler->display->display_options['arguments']['fid']['title_enable'] = TRUE;
  $handler->display->display_options['arguments']['fid']['title'] = '%1';
  $handler->display->display_options['arguments']['fid']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['fid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['fid']['specify_validation'] = TRUE;
  /* Filter criterion: Inhalt: Veröffentlicht */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = '1';
  $handler->display->display_options['filters']['status']['group'] = '0';
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page_1');
  $handler->display->display_options['path'] = 'flag/lists/%';
  $translatables['flag_lists_user_list'] = array(
    t('Defaults'),
    t('more'),
    t('Apply'),
    t('Zurücksetzen'),
    t('Sortierung'),
    t('Asc'),
    t('Desc'),
    t('<h4>Meine Tour: [title_1] | [period_start] - [period_end] | [tour_distance] M</h4>
  <a href="/de/user/touren">Zurück zu meinen Touren</a> | [edit_list]
  <p>[description]</p>
  '),
    t(' | [field_jahr]'),
    t('Tour Bearbeiten'),
    t('Time listed'),
    t('List items weight'),
    t('.'),
    t(','),
    t('All'),
    t('%1'),
    t('Page'),
  );






  return $views;
}
