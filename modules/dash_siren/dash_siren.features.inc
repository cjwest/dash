<?php
/**
 * @file
 * dash_siren.features.inc
 */

/**
 * Implements hook_node_info().
 */
function dash_siren_node_info() {
  $items = array(
    'dash_siren' => array(
      'name' => t('Siren'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Name'),
      'help' => '',
    ),
    'dash_siren_group' => array(
      'name' => t('Siren group'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Name'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
