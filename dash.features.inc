<?php
/**
 * @file
 * dash.features.inc
 */

/**
 * Implements hook_node_info().
 */
function dash_node_info() {

  $items = array(
    'dashboard_item' => array(
      'name' => t('Dashboard Item'),
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
