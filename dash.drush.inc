<?php
/**
 * @file
 * drush commands for Dash Services.
 */

/**
 * Implements hook_drush_command().
 *
 * @return array List of drush commands.
 */
function dash_drush_command() {
  $items = array();

  $items['dash_get_version'] = array(
    'description' => 'Get version information',
    'aliases' => array('dashv'),
  );
  $items['dash_get_all_agents'] = array(
    'description' => 'List all the agents',
    'aliases' => array('dashaa'),
  );
  return $items;

}

function drush_dash_get_all_agents() {
  $client = dash_get_client();
  $agents = dash_get_all_agents($client);
  var_dump($agents);
  drush_log(dt("Retrieved all agents."), "ok");
}

function drush_dash_get_version() {
  $client = dash_get_client();
  $version = dash_get_version($client);
  var_dump($version);
  drush_log(dt("Retrieved version information."), "ok");
}