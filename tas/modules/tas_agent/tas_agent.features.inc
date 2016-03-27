<?php
/**
 * @file
 * tas_agent.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function tas_agent_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_node_info().
 */
function tas_agent_node_info() {
  $items = array(
    'tas_agent' => array(
      'name' => t('TAS Agent'),
      'base' => 'node_content',
      'description' => t('Represents a TAS Agent.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => t('The title of this agent (nombre).'),
    ),
    'tas_group' => array(
      'name' => t('TAS Group'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
