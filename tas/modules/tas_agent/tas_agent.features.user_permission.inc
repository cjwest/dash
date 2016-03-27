<?php
/**
 * @file
 * tas_agent.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function tas_agent_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'create tas_agent content'.
  $permissions['create tas_agent content'] = array(
    'name' => 'create tas_agent content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'delete any tas_agent content'.
  $permissions['delete any tas_agent content'] = array(
    'name' => 'delete any tas_agent content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'delete own tas_agent content'.
  $permissions['delete own tas_agent content'] = array(
    'name' => 'delete own tas_agent content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'delete terms in tags'.
  $permissions['delete terms in tags'] = array(
    'name' => 'delete terms in tags',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'taxonomy',
  );

  // Exported permission: 'delete terms in tas_actions'.
  $permissions['delete terms in tas_actions'] = array(
    'name' => 'delete terms in tas_actions',
    'roles' => array(),
    'module' => 'taxonomy',
  );

  // Exported permission: 'edit any tas_agent content'.
  $permissions['edit any tas_agent content'] = array(
    'name' => 'edit any tas_agent content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'edit own tas_agent content'.
  $permissions['edit own tas_agent content'] = array(
    'name' => 'edit own tas_agent content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'edit terms in tas_actions'.
  $permissions['edit terms in tas_actions'] = array(
    'name' => 'edit terms in tas_actions',
    'roles' => array(),
    'module' => 'taxonomy',
  );

  return $permissions;
}
