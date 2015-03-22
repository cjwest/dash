<?php
/**
 * Created by PhpStorm.
 * User: cjwest
 * Date: 3/21/15
 * Time: 10:03
 */
namespace Dash;
//require_once 'includes/entity.inc';
require_once DRUPAL_ROOT . '/includes/entity.inc';
//module_load_include('inc', 'entity', 'modules/callbacks');
//module_load_include('inc', 'entity', 'includes/entity.property');

class DashItem extends \Entity {

  public function __construct(array $values = array(), $entityType = 'node') {
    parent::__construct($values, $entityType);

    // Expose settings for easier get access.
    if (isset($this->settings)) {
      $ar = $this->settings;
      if (!is_array($this->settings)) {
        $ar = unserialize($this->settings);
      }
      foreach ($ar as $key => $value) {
        if (!isset($this->{$key})) {
          $this->{$key} = $value;
        }
      }
    }
  }

}



