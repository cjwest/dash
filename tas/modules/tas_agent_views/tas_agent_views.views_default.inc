<?php
/**
 * @file
 * tas_agent_views.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function tas_agent_views_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'bats_agents';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'BATS Agents';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Agents';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['style_options']['grouping'] = array(
    0 => array(
      'field' => 'field_tas_group',
      'rendered' => 1,
      'rendered_strip' => 0,
    ),
  );
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Relationship: Content: Taxonomy terms on node */
  $handler->display->display_options['relationships']['term_node_tid']['id'] = 'term_node_tid';
  $handler->display->display_options['relationships']['term_node_tid']['table'] = 'node';
  $handler->display->display_options['relationships']['term_node_tid']['field'] = 'term_node_tid';
  $handler->display->display_options['relationships']['term_node_tid']['label'] = 'Group term';
  $handler->display->display_options['relationships']['term_node_tid']['vocabularies'] = array(
    'tas' => 'tas',
    'stanford_dashboard_site_status' => 0,
    'stanford_dashboard_site_type' => 0,
    'tags' => 0,
    'tas_actions' => 0,
  );
  /* Field: Content: Type */
  $handler->display->display_options['fields']['type']['id'] = 'type';
  $handler->display->display_options['fields']['type']['table'] = 'node';
  $handler->display->display_options['fields']['type']['field'] = 'type';
  $handler->display->display_options['fields']['type']['label'] = '';
  $handler->display->display_options['fields']['type']['exclude'] = TRUE;
  $handler->display->display_options['fields']['type']['element_label_colon'] = FALSE;
  /* Field: Content: Agent ID */
  $handler->display->display_options['fields']['field_tas_agent_id']['id'] = 'field_tas_agent_id';
  $handler->display->display_options['fields']['field_tas_agent_id']['table'] = 'field_data_field_tas_agent_id';
  $handler->display->display_options['fields']['field_tas_agent_id']['field'] = 'field_tas_agent_id';
  $handler->display->display_options['fields']['field_tas_agent_id']['label'] = '';
  $handler->display->display_options['fields']['field_tas_agent_id']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_tas_agent_id']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_tas_agent_id']['type'] = 'text_plain';
  /* Field: Content: Group ID */
  $handler->display->display_options['fields']['field_tas_group_id']['id'] = 'field_tas_group_id';
  $handler->display->display_options['fields']['field_tas_group_id']['table'] = 'field_data_field_tas_group_id';
  $handler->display->display_options['fields']['field_tas_group_id']['field'] = 'field_tas_group_id';
  $handler->display->display_options['fields']['field_tas_group_id']['ui_name'] = 'Content: Group ID';
  $handler->display->display_options['fields']['field_tas_group_id']['label'] = '';
  $handler->display->display_options['fields']['field_tas_group_id']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_tas_group_id']['element_label_colon'] = FALSE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['exclude'] = TRUE;
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['link_to_node'] = FALSE;
  /* Field: Content: Actions */
  $handler->display->display_options['fields']['field_tas_actions']['id'] = 'field_tas_actions';
  $handler->display->display_options['fields']['field_tas_actions']['table'] = 'field_data_field_tas_actions';
  $handler->display->display_options['fields']['field_tas_actions']['field'] = 'field_tas_actions';
  $handler->display->display_options['fields']['field_tas_actions']['label'] = '';
  $handler->display->display_options['fields']['field_tas_actions']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_tas_actions']['alter']['preserve_tags'] = 'a';
  $handler->display->display_options['fields']['field_tas_actions']['element_type'] = 'div';
  $handler->display->display_options['fields']['field_tas_actions']['element_label_type'] = 'div';
  $handler->display->display_options['fields']['field_tas_actions']['element_label_colon'] = FALSE;
  /* Field: Global: View rewrite */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['ui_name'] = 'Global: View rewrite';
  $handler->display->display_options['fields']['nothing']['label'] = '';
  $handler->display->display_options['fields']['nothing']['alter']['text'] = '<div class="btn-group">
  <div class="btn">[title]</div>
  <div class="btn btn-danger"><a class="tas-callback" href="/admin/dash/tas/action/[type]/[field_tas_agent_id]/alert-steady"><strong>Alert</strong> Steady</a></div>
  <div class="btn btn-danger"><a class="tas-callback" href="/admin/dash/tas/action/[type]/[field_tas_agent_id]/alert-wail"><strong>Alert</strong> Wail</a></div>
  <div class="btn btn-primary"><a class="tas-callback" href="/admin/dash/tas/action/[type]/[field_tas_agent_id]/test">Test</a></div>
  <div class="btn btn-success"><a class="tas-callback" href="/admin/dash/tas/action/[type]/[field_tas_agent_id]/reset">Reset</a></div>
</div>';
  $handler->display->display_options['fields']['nothing']['element_label_colon'] = FALSE;
  /* Field: Content: Local Activation */
  $handler->display->display_options['fields']['field_tas_local_activation']['id'] = 'field_tas_local_activation';
  $handler->display->display_options['fields']['field_tas_local_activation']['table'] = 'field_data_field_tas_local_activation';
  $handler->display->display_options['fields']['field_tas_local_activation']['field'] = 'field_tas_local_activation';
  $handler->display->display_options['fields']['field_tas_local_activation']['element_type'] = 'div';
  $handler->display->display_options['fields']['field_tas_local_activation']['element_label_type'] = 'div';
  $handler->display->display_options['fields']['field_tas_local_activation']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['field_tas_local_activation']['type'] = 'taxonomy_term_reference_plain';
  /* Field: Content: Edit link */
  $handler->display->display_options['fields']['edit_node']['id'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['edit_node']['field'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['label'] = '';
  $handler->display->display_options['fields']['edit_node']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['edit_node']['alter']['text'] = '<div class="edit-link">[edit_node]</div>';
  $handler->display->display_options['fields']['edit_node']['element_type'] = 'div';
  $handler->display->display_options['fields']['edit_node']['element_label_type'] = 'div';
  $handler->display->display_options['fields']['edit_node']['element_label_colon'] = FALSE;
  /* Sort criterion: Taxonomy term: Weight */
  $handler->display->display_options['sorts']['weight']['id'] = 'weight';
  $handler->display->display_options['sorts']['weight']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['sorts']['weight']['field'] = 'weight';
  $handler->display->display_options['sorts']['weight']['relationship'] = 'term_node_tid';
  /* Sort criterion: Content: Type */
  $handler->display->display_options['sorts']['type']['id'] = 'type';
  $handler->display->display_options['sorts']['type']['table'] = 'node';
  $handler->display->display_options['sorts']['type']['field'] = 'type';
  $handler->display->display_options['sorts']['type']['order'] = 'DESC';
  /* Sort criterion: Content: Title */
  $handler->display->display_options['sorts']['title']['id'] = 'title';
  $handler->display->display_options['sorts']['title']['table'] = 'node';
  $handler->display->display_options['sorts']['title']['field'] = 'title';
  $handler->display->display_options['sorts']['title']['order'] = 'DESC';
  /* Contextual filter: Content: Has taxonomy term ID (with depth) */
  $handler->display->display_options['arguments']['term_node_tid_depth']['id'] = 'term_node_tid_depth';
  $handler->display->display_options['arguments']['term_node_tid_depth']['table'] = 'node';
  $handler->display->display_options['arguments']['term_node_tid_depth']['field'] = 'term_node_tid_depth';
  $handler->display->display_options['arguments']['term_node_tid_depth']['exception']['title_enable'] = TRUE;
  $handler->display->display_options['arguments']['term_node_tid_depth']['title_enable'] = TRUE;
  $handler->display->display_options['arguments']['term_node_tid_depth']['title'] = '%1 Group';
  $handler->display->display_options['arguments']['term_node_tid_depth']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['term_node_tid_depth']['default_argument_options']['argument'] = 'all';
  $handler->display->display_options['arguments']['term_node_tid_depth']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['term_node_tid_depth']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['term_node_tid_depth']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['term_node_tid_depth']['specify_validation'] = TRUE;
  $handler->display->display_options['arguments']['term_node_tid_depth']['validate']['type'] = 'taxonomy_term';
  $handler->display->display_options['arguments']['term_node_tid_depth']['validate_options']['vocabularies'] = array(
    'tas' => 'tas',
  );
  $handler->display->display_options['arguments']['term_node_tid_depth']['validate_options']['type'] = 'convert';
  $handler->display->display_options['arguments']['term_node_tid_depth']['validate_options']['transform'] = TRUE;
  $handler->display->display_options['arguments']['term_node_tid_depth']['validate']['fail'] = 'ignore';
  $handler->display->display_options['arguments']['term_node_tid_depth']['depth'] = '0';
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'tas_agent' => 'tas_agent',
  );
  /* Filter criterion: Content: Title */
  $handler->display->display_options['filters']['title']['id'] = 'title';
  $handler->display->display_options['filters']['title']['table'] = 'node';
  $handler->display->display_options['filters']['title']['field'] = 'title';
  $handler->display->display_options['filters']['title']['operator'] = 'not';
  $handler->display->display_options['filters']['title']['value'] = 'importer';

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'bats/agents';
  $export['bats_agents'] = $view;

  $view = new view();
  $view->name = 'bats_groups';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'BATS Groups';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'BATS Groups';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Relationship: Content: Taxonomy terms on node */
  $handler->display->display_options['relationships']['term_node_tid']['id'] = 'term_node_tid';
  $handler->display->display_options['relationships']['term_node_tid']['table'] = 'node';
  $handler->display->display_options['relationships']['term_node_tid']['field'] = 'term_node_tid';
  $handler->display->display_options['relationships']['term_node_tid']['label'] = 'Group term';
  $handler->display->display_options['relationships']['term_node_tid']['vocabularies'] = array(
    'tas' => 'tas',
    'stanford_dashboard_site_status' => 0,
    'stanford_dashboard_site_type' => 0,
    'tags' => 0,
    'tas_actions' => 0,
  );
  /* Field: Content: Type */
  $handler->display->display_options['fields']['type']['id'] = 'type';
  $handler->display->display_options['fields']['type']['table'] = 'node';
  $handler->display->display_options['fields']['type']['field'] = 'type';
  $handler->display->display_options['fields']['type']['label'] = '';
  $handler->display->display_options['fields']['type']['exclude'] = TRUE;
  $handler->display->display_options['fields']['type']['element_label_colon'] = FALSE;
  /* Field: Content: Group ID */
  $handler->display->display_options['fields']['field_tas_group_id']['id'] = 'field_tas_group_id';
  $handler->display->display_options['fields']['field_tas_group_id']['table'] = 'field_data_field_tas_group_id';
  $handler->display->display_options['fields']['field_tas_group_id']['field'] = 'field_tas_group_id';
  $handler->display->display_options['fields']['field_tas_group_id']['ui_name'] = 'Content: Group ID';
  $handler->display->display_options['fields']['field_tas_group_id']['label'] = '';
  $handler->display->display_options['fields']['field_tas_group_id']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_tas_group_id']['element_label_colon'] = FALSE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['exclude'] = TRUE;
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['link_to_node'] = FALSE;
  /* Field: Content: Actions */
  $handler->display->display_options['fields']['field_tas_actions']['id'] = 'field_tas_actions';
  $handler->display->display_options['fields']['field_tas_actions']['table'] = 'field_data_field_tas_actions';
  $handler->display->display_options['fields']['field_tas_actions']['field'] = 'field_tas_actions';
  $handler->display->display_options['fields']['field_tas_actions']['label'] = '';
  $handler->display->display_options['fields']['field_tas_actions']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_tas_actions']['alter']['text'] = '[field_tas_actions]';
  $handler->display->display_options['fields']['field_tas_actions']['alter']['preserve_tags'] = 'a';
  $handler->display->display_options['fields']['field_tas_actions']['element_type'] = 'div';
  $handler->display->display_options['fields']['field_tas_actions']['element_label_type'] = 'div';
  $handler->display->display_options['fields']['field_tas_actions']['element_label_colon'] = FALSE;
  /* Field: Content: Group */
  $handler->display->display_options['fields']['field_tas_group']['id'] = 'field_tas_group';
  $handler->display->display_options['fields']['field_tas_group']['table'] = 'field_data_field_tas_group';
  $handler->display->display_options['fields']['field_tas_group']['field'] = 'field_tas_group';
  $handler->display->display_options['fields']['field_tas_group']['label'] = '';
  $handler->display->display_options['fields']['field_tas_group']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_tas_group']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_tas_group']['type'] = 'taxonomy_term_reference_plain';
  /* Field: Global: Custom text */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['label'] = '';
  $handler->display->display_options['fields']['nothing']['alter']['text'] = '<div class="btn-group">
  <div class="btn"><strong>[title]</strong></div>
  <div class="btn btn-danger"><a class="tas-callback" href="/admin/dash/tas/action/[type]/[field_tas_group_id]/alert-steady"><strong>Alert</strong> Steady</a></div>
  <div class="btn btn-danger"><a class="tas-callback" href="/admin/dash/tas/action/[type]/[field_tas_group_id]/alert-wail"><strong>Alert</strong> Wail</a></div>
  <div class="btn btn-primary"><a class="tas-callback" href="/admin/dash/tas/action/[type]/[field_tas_group_id]/test">Test</a></div>
  <div class="btn btn-success"><a class="tas-callback" href="/admin/dash/tas/action/[type]/[field_tas_group_id]/reset">Reset</a></div>
  <div class="btn"><a href="/bats/agents/[field_tas_group]">See [field_tas_group] Agents >></a></div>
</div>';
  $handler->display->display_options['fields']['nothing']['alter']['strip_tags'] = TRUE;
  $handler->display->display_options['fields']['nothing']['alter']['preserve_tags'] = '<a> <button> <div> <strong> <p>';
  $handler->display->display_options['fields']['nothing']['element_type'] = 'div';
  $handler->display->display_options['fields']['nothing']['element_label_type'] = 'div';
  $handler->display->display_options['fields']['nothing']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['nothing']['hide_alter_empty'] = TRUE;
  /* Field: Content: Edit link */
  $handler->display->display_options['fields']['edit_node']['id'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['edit_node']['field'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['label'] = '';
  $handler->display->display_options['fields']['edit_node']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['edit_node']['alter']['text'] = '<div class="edit-link">[edit_node]</div>';
  $handler->display->display_options['fields']['edit_node']['element_type'] = 'div';
  $handler->display->display_options['fields']['edit_node']['element_label_type'] = 'div';
  $handler->display->display_options['fields']['edit_node']['element_label_colon'] = FALSE;
  /* Sort criterion: Taxonomy term: Weight */
  $handler->display->display_options['sorts']['weight']['id'] = 'weight';
  $handler->display->display_options['sorts']['weight']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['sorts']['weight']['field'] = 'weight';
  $handler->display->display_options['sorts']['weight']['relationship'] = 'term_node_tid';
  /* Sort criterion: Content: Title */
  $handler->display->display_options['sorts']['title']['id'] = 'title';
  $handler->display->display_options['sorts']['title']['table'] = 'node';
  $handler->display->display_options['sorts']['title']['field'] = 'title';
  $handler->display->display_options['sorts']['title']['order'] = 'DESC';
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'tas_group' => 'tas_group',
  );
  /* Filter criterion: Content: Title */
  $handler->display->display_options['filters']['title']['id'] = 'title';
  $handler->display->display_options['filters']['title']['table'] = 'node';
  $handler->display->display_options['filters']['title']['field'] = 'title';
  $handler->display->display_options['filters']['title']['operator'] = 'not';
  $handler->display->display_options['filters']['title']['value'] = 'importer';

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'bats/groups';
  $export['bats_groups'] = $view;

  $view = new view();
  $view->name = 'tas_dashboard';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'TAS Dashboard';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'TAS Dashboard';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['style_options']['grouping'] = array(
    0 => array(
      'field' => 'field_tas_group',
      'rendered' => 1,
      'rendered_strip' => 0,
    ),
  );
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Relationship: Content: Taxonomy terms on node */
  $handler->display->display_options['relationships']['term_node_tid']['id'] = 'term_node_tid';
  $handler->display->display_options['relationships']['term_node_tid']['table'] = 'node';
  $handler->display->display_options['relationships']['term_node_tid']['field'] = 'term_node_tid';
  $handler->display->display_options['relationships']['term_node_tid']['label'] = 'Group term';
  $handler->display->display_options['relationships']['term_node_tid']['vocabularies'] = array(
    'tas' => 'tas',
    'stanford_dashboard_site_status' => 0,
    'stanford_dashboard_site_type' => 0,
    'tags' => 0,
    'tas_actions' => 0,
  );
  /* Field: Content: Type */
  $handler->display->display_options['fields']['type']['id'] = 'type';
  $handler->display->display_options['fields']['type']['table'] = 'node';
  $handler->display->display_options['fields']['type']['field'] = 'type';
  $handler->display->display_options['fields']['type']['label'] = '';
  $handler->display->display_options['fields']['type']['exclude'] = TRUE;
  $handler->display->display_options['fields']['type']['element_label_colon'] = FALSE;
  /* Field: Content: Agent ID */
  $handler->display->display_options['fields']['field_tas_agent_id']['id'] = 'field_tas_agent_id';
  $handler->display->display_options['fields']['field_tas_agent_id']['table'] = 'field_data_field_tas_agent_id';
  $handler->display->display_options['fields']['field_tas_agent_id']['field'] = 'field_tas_agent_id';
  $handler->display->display_options['fields']['field_tas_agent_id']['label'] = '';
  $handler->display->display_options['fields']['field_tas_agent_id']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_tas_agent_id']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_tas_agent_id']['type'] = 'text_plain';
  /* Field: Content: Group ID */
  $handler->display->display_options['fields']['field_tas_group_id']['id'] = 'field_tas_group_id';
  $handler->display->display_options['fields']['field_tas_group_id']['table'] = 'field_data_field_tas_group_id';
  $handler->display->display_options['fields']['field_tas_group_id']['field'] = 'field_tas_group_id';
  $handler->display->display_options['fields']['field_tas_group_id']['ui_name'] = 'Content: Group ID';
  $handler->display->display_options['fields']['field_tas_group_id']['label'] = '';
  $handler->display->display_options['fields']['field_tas_group_id']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_tas_group_id']['element_label_colon'] = FALSE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['exclude'] = TRUE;
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['link_to_node'] = FALSE;
  /* Field: Content: Agent ID for Title */
  $handler->display->display_options['fields']['field_tas_agent_id_1']['id'] = 'field_tas_agent_id_1';
  $handler->display->display_options['fields']['field_tas_agent_id_1']['table'] = 'field_data_field_tas_agent_id';
  $handler->display->display_options['fields']['field_tas_agent_id_1']['field'] = 'field_tas_agent_id';
  $handler->display->display_options['fields']['field_tas_agent_id_1']['ui_name'] = 'Content: Agent ID for Title';
  $handler->display->display_options['fields']['field_tas_agent_id_1']['label'] = '';
  $handler->display->display_options['fields']['field_tas_agent_id_1']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_tas_agent_id_1']['alter']['text'] = '[title]';
  $handler->display->display_options['fields']['field_tas_agent_id_1']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_tas_agent_id_1']['type'] = 'text_plain';
  /* Field: Content: Group ID for Title */
  $handler->display->display_options['fields']['field_tas_group_id_1']['id'] = 'field_tas_group_id_1';
  $handler->display->display_options['fields']['field_tas_group_id_1']['table'] = 'field_data_field_tas_group_id';
  $handler->display->display_options['fields']['field_tas_group_id_1']['field'] = 'field_tas_group_id';
  $handler->display->display_options['fields']['field_tas_group_id_1']['ui_name'] = 'Content: Group ID for Title';
  $handler->display->display_options['fields']['field_tas_group_id_1']['label'] = '';
  $handler->display->display_options['fields']['field_tas_group_id_1']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_tas_group_id_1']['alter']['text'] = '<h4>[title] - Group</h4>';
  $handler->display->display_options['fields']['field_tas_group_id_1']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_tas_group_id_1']['type'] = 'text_plain';
  /* Field: Content: Actions */
  $handler->display->display_options['fields']['field_tas_actions']['id'] = 'field_tas_actions';
  $handler->display->display_options['fields']['field_tas_actions']['table'] = 'field_data_field_tas_actions';
  $handler->display->display_options['fields']['field_tas_actions']['field'] = 'field_tas_actions';
  $handler->display->display_options['fields']['field_tas_actions']['label'] = '';
  $handler->display->display_options['fields']['field_tas_actions']['alter']['preserve_tags'] = 'a';
  $handler->display->display_options['fields']['field_tas_actions']['element_type'] = 'div';
  $handler->display->display_options['fields']['field_tas_actions']['element_label_type'] = 'div';
  $handler->display->display_options['fields']['field_tas_actions']['element_label_colon'] = FALSE;
  /* Field: Content: Group */
  $handler->display->display_options['fields']['field_tas_group']['id'] = 'field_tas_group';
  $handler->display->display_options['fields']['field_tas_group']['table'] = 'field_data_field_tas_group';
  $handler->display->display_options['fields']['field_tas_group']['field'] = 'field_tas_group';
  $handler->display->display_options['fields']['field_tas_group']['label'] = '';
  $handler->display->display_options['fields']['field_tas_group']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_tas_group']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_tas_group']['alter']['text'] = '[field_tas_group][field_tas_actions]';
  $handler->display->display_options['fields']['field_tas_group']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_tas_group']['type'] = 'taxonomy_term_reference_plain';
  /* Field: Content: Local Activation */
  $handler->display->display_options['fields']['field_tas_local_activation']['id'] = 'field_tas_local_activation';
  $handler->display->display_options['fields']['field_tas_local_activation']['table'] = 'field_data_field_tas_local_activation';
  $handler->display->display_options['fields']['field_tas_local_activation']['field'] = 'field_tas_local_activation';
  $handler->display->display_options['fields']['field_tas_local_activation']['element_type'] = 'div';
  $handler->display->display_options['fields']['field_tas_local_activation']['element_label_type'] = 'div';
  $handler->display->display_options['fields']['field_tas_local_activation']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['field_tas_local_activation']['type'] = 'taxonomy_term_reference_plain';
  /* Field: Content: Edit link */
  $handler->display->display_options['fields']['edit_node']['id'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['edit_node']['field'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['label'] = '';
  $handler->display->display_options['fields']['edit_node']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['edit_node']['alter']['text'] = '<div class="edit-link">[edit_node]</div>';
  $handler->display->display_options['fields']['edit_node']['element_type'] = 'div';
  $handler->display->display_options['fields']['edit_node']['element_label_type'] = 'div';
  $handler->display->display_options['fields']['edit_node']['element_label_colon'] = FALSE;
  /* Sort criterion: Taxonomy term: Weight */
  $handler->display->display_options['sorts']['weight']['id'] = 'weight';
  $handler->display->display_options['sorts']['weight']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['sorts']['weight']['field'] = 'weight';
  $handler->display->display_options['sorts']['weight']['relationship'] = 'term_node_tid';
  /* Sort criterion: Content: Type */
  $handler->display->display_options['sorts']['type']['id'] = 'type';
  $handler->display->display_options['sorts']['type']['table'] = 'node';
  $handler->display->display_options['sorts']['type']['field'] = 'type';
  $handler->display->display_options['sorts']['type']['order'] = 'DESC';
  /* Sort criterion: Content: Title */
  $handler->display->display_options['sorts']['title']['id'] = 'title';
  $handler->display->display_options['sorts']['title']['table'] = 'node';
  $handler->display->display_options['sorts']['title']['field'] = 'title';
  $handler->display->display_options['sorts']['title']['order'] = 'DESC';
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'tas_agent' => 'tas_agent',
    'tas_group' => 'tas_group',
  );
  /* Filter criterion: Content: Title */
  $handler->display->display_options['filters']['title']['id'] = 'title';
  $handler->display->display_options['filters']['title']['table'] = 'node';
  $handler->display->display_options['filters']['title']['field'] = 'title';
  $handler->display->display_options['filters']['title']['operator'] = 'not';
  $handler->display->display_options['filters']['title']['value'] = 'importer';

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'tas/dashboard';

  /* Display: Embed */
  $handler = $view->new_display('embed', 'Embed', 'embed_1');
  $export['tas_dashboard'] = $view;

  return $export;
}
