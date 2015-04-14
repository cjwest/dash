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

  /**
   * Overridden.
   * @see EntityAPIController#__construct()
   */
  public function __construct($entityType = 'node') {
    parent::__construct($entityType);
  }

    /**
   * Implements EntityAPIController.
   *
   * The create() method is responsible for the default values of entity properties
   * when creating a new object. It is imperative that our entity has values when
   * saving the object. In order to create an 'empty' entity we use the
   * entity_create function.
   */
  public function create(array $values = array()) {
    /*
    global $user;
    $values += array(
      'title' => '',
      'description' => '',
      'created' => REQUEST_TIME,
      'changed' => REQUEST_TIME,
      'uid' => $user->uid,
    );
    */
    return parent::create($values);
  }
  /**
   * Implements EntityAPIController::buildContent.
   *
   * @param $content
   *   Optionally. Allows pre-populating the built content to ease overridding
   *   this method.
   */
  public function buildContent($entity, $view_mode = 'full', $langcode = NULL, $content = array()) {
    $wrapper = entity_metadata_wrapper('dashboard_item', $entity);
    return parent::buildContent($entity, $view_mode, $langcode, $content);
  }

    /**
   * Overridden.
   * @see EntityAPIController::save($entity)
  */
  public function save($entity) {

    return parent::save($entity);
  }

    /**
   * Overridden.
   * @see EntityAPIController::load($ids, $conditions)
   *
   * In contrast to the parent implementation we factor out query execution, so
   * fetching can be further customized easily.
   */

  public function load($ids = array(), $conditions = array()) {
    $dash_items = array();

    if (empty($ids)){
      $query = new DashEntityFieldQuery();
      $result = $query->execute();

      if (isset($result['node'])) {
        $ids = array_keys($result['node']);
        $dash_items = parent::load($ids, $conditions);
// same result        $entities = entity_load_multiple_by_name('node', isset($ids) ? array($ids) : FALSE);
      }
    }
    else {
      $dash_items = parent::load($ids, $conditions);
    }
   return $dash_items;
  }


  public function getAllDashItems() {
    $dash_items = array();
    $query = new DashEntityFieldQuery();

    $result = $query->execute();

    if (isset($result['node'])) {
      $dash_nids = array_keys($result['node']);
      $dash_items = parent::load($dash_nids, array());
    }
    return $dash_items;

  }
  public function getStatus ($dash_items) {
    foreach ($dash_items as $item) {
      DashItem::getStatus($item);
    }
  }
}

class DashEntityFieldQuery extends EntityFieldQuery {
  public function __construct() {
    // now we don't need to define these over and over anymore
    $this
      ->entityCondition('entity_type', 'node')
      ->propertyCondition('status', NODE_PUBLISHED)
      ->entityCondition('bundle', 'dashboard_item')
      ->propertyOrderBy('created', 'DESC');

     }
}