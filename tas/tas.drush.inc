<?php
/**
 * @file
 * drush commands for Tas Services.
 */

/**
 * Implements hook_drush_command().
 *
 * @return array List of drush commands.
 */
function tas_drush_command() {
  $items = array();

  $items['tas_get_version'] = array(
    'description' => 'Get TAS version information',
    'aliases' => array('tasv'),
  );
  $items['tas_get_all_agents'] = array(
    'description' => 'List all the TAS agents',
    'aliases' => array('tasaa'),
  );
  $items['tas_get_all'] = array(
    'description' => 'List all the TAS agents and info',
    'aliases' => array('tasa'),
  );
  return $items;

}

function drush_tas_get_all_agents() {
  $client = tas_get_client();
  $agents = tas_get_all_agents($client);
  var_dump($agents);
  drush_log(dt("Retrieved all TAS agents."), "ok");
}

function drush_tas_get_version() {
  $client = tas_get_client();
  $version = tas_get_version($client);
  var_dump($version);
  drush_log(dt("Retrieved TAS version information."), "ok");
}

function drush_tas_get_all() {
  $client = tas_get_client();
  $agents = tas_get_all($client);
  var_dump($agents);
  drush_log(dt("Retrieved all TAS agents and info."), "ok");
}
