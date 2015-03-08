<?php
/**
 * @file
 * @author [cjwest] <[cjwest@acm.org]>
 */

use Dash\DashClient;

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



  $result = ' ';
  $error = false;

  $query = new EntityFieldQuery();
  $query->entityCondition('entity_type', 'node')
    ->entityCondition('bundle', 'dashboard_item')
    ->propertyCondition('status', NODE_PUBLISHED);

  $result = $query->execute();

  $aids = array();
  foreach($result['artwork'] as $record) {
    $aids[] = $record->aid;
  }
  $artworks = entity_load('artwork', $aids);

  $client = DashClient::factory(array(
    'base_url'        => 'https://api.github.com/user',
    'consumer_key'    => 'xxxxx',
    'consumer_secret' => 'xxxxx',
  ));
  try {
      $res = $client->get("https://api.github.com/user", ['auth' =>  ['xxxxx', 'xxxxx']]);
    } catch (\Exception $e) {
      $result = $result . "<p>Caught Exception: " . $e->getMessage() . '</p>';
      $error = true;
    }
    if ($error == false) {
      $result = $result . "<p>Status Code: " . $res->getStatusCode() . '</p>';
      $result = $result . '<p>Header: ' . $res->getHeader('content-type') . '</p>';
      $result = $result . '<p>Body: ' . $res->getBody() . '</p>';

      var_export($res->json());

    }

  $result = "<p>" . t("Client Get.") . $result . "</p>";
  $output['content']['body']['#markup'] = $result;

  return $output;
}