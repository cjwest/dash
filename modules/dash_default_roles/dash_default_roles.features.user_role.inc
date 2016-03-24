<?php
/**
 * @file
 * dash_default_roles.features.user_role.inc
 */

/**
 * Implements hook_user_default_roles().
 */
function dash_default_roles_user_default_roles() {
  $roles = array();

  // Exported role: ATI.
  $roles['ATI'] = array(
    'name' => 'ATI',
    'weight' => 3,
  );

  // Exported role: ATI Administrator.
  $roles['ATI Administrator'] = array(
    'name' => 'ATI Administrator',
    'weight' => 4,
  );

  return $roles;
}
