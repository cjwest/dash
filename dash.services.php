<?php
/**
 * @file
 * Contains services for dash
 */

require_once "includes/vendor/autoload.php";
use GuzzleHttp\Client;
/**
 * Update the display
 */
function dash_update(){

  watchdog('dash', t("Begin updating dash information."));

echo "Updating Dash information";

$client = new Client([
    'base_uri' => 'https://demo.theftalertsystem.com:8443/tas_console/include/api.php',
  ]
);
$response = $client->get('?info=version');

var_dump($response);
$content = '';

$content = $content . "<p>Status Code: " . $response->getStatusCode() . '</p>';
$content = $content . '<p>Header: ' . $response->getHeader('content-type') . '</p>';
$content = $content . '<p>Body: ' . $response->getBody() . '</p>';

echo $content;

$response = $client->get(
  '?op=get&op2=all_agents&return_type=json&other_mode=url_encode_separator_|&apipass=5875&user=rmt_ctl&pass=8765');

$content = $content . "<p>Status Code: " . $response->getStatusCode() . '</p>';
$content = $content . '<p>Header: ' . $response->getHeader('content-type') . '</p>';
$content = $content . '<p>Body: ' . $response->getBody() . '</p>';

$result = json_decode($response->getBody(), true);

var_dump($result);

  watchdog('dash', t("Finished updating dash information."));
}