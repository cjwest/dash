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


  $items['tas'] = array(
    'description' => 'Get TAS data',
    'aliases' => array('tas'),
    'options' => array(
      'agents' => 'Display TAS agents.',
      'info' => 'Display TAS agents and info.',
    ),

    'examples' => array(
      'drush tas help' => 'Displays help information.',
      'drush tas' => 'Displays TAS version information.',
      'drush tas --agents' => 'Displays TAS agents.',
      'drush tas --info' => 'Displays TAS agents and info.',
    ),
  );

  return $items;

}

function drush_tas($type = FALSE) {

  $client = tas_get_client();

  // Options
  $agents = strtolower(drush_get_option('agents'));
  if (!empty($agents)) {
    $result = tas_get_all_agents($client);
    var_dump($result);
    drush_log(dt("Retrieved TAS agents."), "ok");
  }

  $all = strtolower(drush_get_option('info'));
  if (!empty($all)) {
    $result = tas_get_all($client);
    var_dump($result);
    drush_log(dt("Retrieved TAS agents and info."), "ok");
  }

  if (!$agents && !$all) {
    $result = tas_get_version($client);
    var_dump($result);
    drush_log(dt("Retrieved TAS version information."), "ok");
  }
}
