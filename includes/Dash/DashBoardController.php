<?php
/**
 * Created by PhpStorm.
 * User: cjwest
 * Date: 3/21/15
 * Time: 10:03
 */
namespace Dash;
use EntityFieldQuery;
use Dash\DashItem;
//require_once 'includes/entity.inc';
require_once DRUPAL_ROOT . '/includes/entity.inc';
//module_load_include('inc', 'entity', 'modules/callbacks');
//module_load_include('inc', 'entity', 'includes/entity.property');

class DashBoardController extends \EntityAPIController {

  public function getAllDashItems() {
    $dash_items = array();
    var_dump(DRUPAL_ROOT . '/includes/entity.inc');
    print_r(DRUPAL_ROOT);

/*  Okay, what is the secret handshake here?
    $conditions = array();
    $ids = array();
    $result = parent::query($ids, $conditions);
    $dash_items = parent::load($ids, $result);
    $dash_items = parent::load();

    $dash_items = dash_getAllDashItems();
*/
    $query = new EntityFieldQuery();
    $query->entityCondition('entity_type', 'node')
      ->entityCondition('bundle', 'dashboard_item')
      ->propertyCondition('status', NODE_PUBLISHED);


    $result = $query->execute();

    if (isset($result['node'])) {
      $dash_nids = array_keys($result['node']);
      $dash_items = entity_load('node', $dash_nids);
      $dash_item = new DashItem();
    }
    return $dash_items;

  }
}



