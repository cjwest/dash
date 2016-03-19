<?php
/**
 * Register Dash namespace with PHP's spl_autoload_register
 */
define('DashPATH', realpath(dirname(__FILE__)));
function dash_autoloader($class) {
  $filename = DashPATH . '/' . str_replace('\\', '/', $class) . '.php';
  if (file_exists($filename)) {
    include_once($filename);
  }
}
spl_autoload_register('dash_autoloader');