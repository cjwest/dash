<?php
/**
 * @file
 * @author [cjwest] <[cjwest@acm.org]>
 */

use Dash\DashClient;
use Dash\DashBoardController;
use Dash\DashItem;
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

//  $dash_items = dash_getAllDashItems();
  $dashboard_controller = new DashBoardController('node');
  $dash_items = $dashboard_controller->load();
  $dashboard_controller->getStatus($dash_items);

  $content = ' ';

  $content = "<p>" . t("Client Get.") . $content . "</p>";
  $output['content']['body']['#markup'] = $content;


  return $output;
}
