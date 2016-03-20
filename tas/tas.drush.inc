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
      'force-alert' => 'Forces a TAS alert.',
    ),

    'examples' => array(
      'drush tas help' => 'Displays help information.',
      'drush tas' => 'Displays TAS version information.',
      'drush tas --agents' => 'Displays TAS agents.',
      'drush tas --force-alert' => 'Forces a TAS alert.',
    ),
  );

  return $items;

}

function drush_tas($type = FALSE) {

  $client = tas_get_client();

  // Options
  $option = strtolower(drush_get_option('agents'));
  if (!empty($option)) {
    $result = tas_get_all_agents($client);
    var_dump($result);
    drush_log(dt("Retrieved TAS agents."), "ok");
  }

  $option = strtolower(drush_get_option('force-alert'));
  if (!empty($option)) {
    $result = tas_force_alert($client);
    var_dump($result);
    if (!empty($result)) {
      drush_log(dt("Forced alert."), "ok");
    }
    else {
      drush_log(dt("Forced alert unsuccessful."), "ok");
    }
  }

  if (!$option) {
    $result = tas_get_version($client);
    var_dump($result);
    drush_log(dt("Retrieved TAS version information."), "ok");
  }
}
