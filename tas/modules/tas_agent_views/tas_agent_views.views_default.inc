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
  /* Field: Content: Agent ID */
  $handler->display->display_options['fields']['field_tas_agent_id']['id'] = 'field_tas_agent_id';
  $handler->display->display_options['fields']['field_tas_agent_id']['table'] = 'field_data_field_tas_agent_id';
  $handler->display->display_options['fields']['field_tas_agent_id']['field'] = 'field_tas_agent_id';
  $handler->display->display_options['fields']['field_tas_agent_id']['label'] = '';
  $handler->display->display_options['fields']['field_tas_agent_id']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_tas_agent_id']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_tas_agent_id']['type'] = 'text_plain';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['link_to_node'] = FALSE;
  /* Field: Content: Local Activation */
  $handler->display->display_options['fields']['field_tas_local_activation']['id'] = 'field_tas_local_activation';
  $handler->display->display_options['fields']['field_tas_local_activation']['table'] = 'field_data_field_tas_local_activation';
  $handler->display->display_options['fields']['field_tas_local_activation']['field'] = 'field_tas_local_activation';
  $handler->display->display_options['fields']['field_tas_local_activation']['type'] = 'taxonomy_term_reference_plain';
  /* Field: Global: Alert Steady */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['ui_name'] = 'Global: Alert Steady';
  $handler->display->display_options['fields']['nothing']['label'] = '';
  $handler->display->display_options['fields']['nothing']['alter']['text'] = '<a class="tas-callback" href="/admin/dash/tas/action/[field_tas_agent_id]/alert-steady"><strong>Alert</strong> Steady</a>';
  $handler->display->display_options['fields']['nothing']['element_label_colon'] = FALSE;
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

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'tas/dashboard';
  $export['tas_dashboard'] = $view;

  return $export;
}
