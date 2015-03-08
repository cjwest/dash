<?php
/**
 * @file
 * @author [cjwest] <[cjwest@acm.org]>
 */

use Dash\DashClient;
require_once 'includes/entity.inc';

function dash_admin_config() {
  $output = array();

  // Management Menu.
//  $menu_block = dash_management_menu_block();
//  $output['content']['dash_menu_block'] = $menu_block;

  // Connection Status Block.
//  $block = block_load('dash', 'connection_status');
//  $output['content']['connection_block'] = _block_get_renderable_array(_block_render_blocks(array($block)));

  // Header
  $output['content']['thetext']['#markup'] = "<h2>" . t('Items') . "</h2>";

  // The view.
  //$output['content']['overviewview']['#markup'] = views_embed_view('importers_overview_page');

  return $output;
}

function dash_admin_config_connect() {
  $output = array();

  // Management Menu.
//  $menu_block = dash_management_menu_block();
//  $output['content']['dash_menu_block'] = $menu_block;

  // The settings form found in stanford_capx.forms.inc
  //$form = drupal_get_form('dash_forms_connect_form');
  //$output['content']['config_form'] = $form;




  $query = new EntityFieldQuery();
  $query->entityCondition('entity_type', 'node')
    ->entityCondition('bundle', 'dashboard_item')
    ->propertyCondition('status', NODE_PUBLISHED);

  $result = $query->execute();

  if (isset($result['node'])) {
    $dash_nids = array_keys($result['node']);
    $dash_items = entity_load('node', $dash_nids);
  }

  $content = ' ';
  $error = false;

  foreach ($dash_items as $item) {
     dsm ($item);
     $content = $content . '<p>URL: ' . $item->field_dash_item_url['und']['0']['url'] . '</p>';
     $content = $content . '<p>User: ' . $item->field_dash_item_user['und']['0']['safe_value'] . '</p>';
     $content = $content . '<p>Password: ' . $item->field_dash_item_password['und']['0']['safe_value'] . '</p>';


     $client = DashClient::factory(array(
      'base_url'        => $item->field_dash_item_url['und']['0']['url'],
      'consumer_key'    => $item->field_dash_item_user['und']['0']['safe_value'],
      'consumer_secret' => $item->field_dash_item_password['und']['0']['safe_value'],
    ));
    try {
      $res = $client->get($item->field_dash_item_url['und']['0']['url'],
        ['auth' =>  [$item->field_dash_item_user['und']['0']['safe_value'],
          $item->field_dash_item_password['und']['0']['safe_value']]]);
      } catch (\Exception $e) {
        $content = $result . "<p>Caught Exception: " . $e->getMessage() . '</p>';
        $error = true;
      }
      if ($error == false) {
        $content = $content . "<p>Status Code: " . $res->getStatusCode() . '</p>';
        $content = $content . '<p>Header: ' . $res->getHeader('content-type') . '</p>';
        $content = $content . '<p>Body: ' . $res->getBody() . '</p>';

        var_export($res->json());
      }
    }

  $content = "<p>" . t("Client Get.") . $content . "</p>";
  $output['content']['body']['#markup'] = $content;

  return $output;
}
