<?php
/**
 * Created by PhpStorm.
 * User: cjwest
 * Date: 3/7/15
 * Time: 14:20
 *
 * @file
 * Dash HTTPClient extending Guzzle :)
 * This client is used for communicating with the various endpoints.
 * The base of this class is the Guzzle HTTP client.
 *
 * Some API functions require an authentication token. This can be obtained
 * through the AuthLib and the authenticate() method.
 *
 * EXAMPLES:
 *
 * $client = new HTTPClient();
 *
 * $auth = $client->api('auth');
 * $auth->authenticate('username', 'password');
 * $token = $auth->getAuthToken();
 *
 * $client->setAPIToken($token);
 *
 * $schema = $client->api('schema')->profile();
 */

namespace Dash;

use GuzzleHttp\Client as GuzzleClient;
use GuzzleHttp\Collection;
//use Guzzle\Plugin\Oauth\OauthPlugin;
//use Guzzle\Service\Description\ServiceDescription;

/**
 * A simple Dash API client
 */
class DashClient extends GuzzleClient
{
  public static function factory($config = array())
  {
    // Provide a hash of default client configuration options
//    $default = array('base_url' => 'https://api.github.com/user');
    $default = array();

    // The following values are required when creating the client
    $required = array(
      'base_url',
      'consumer_key',
      'consumer_secret',
    );

    // Merge in default settings and validate the config
    $config = Collection::fromConfig($config, $default, $required);

    // Create a new Dash client
    $client = new self($config->getKeys());
    /*
        // Ensure that the OauthPlugin is attached to the client
        $client->addSubscriber(new OauthPlugin($config->toArray()));
    */
    return $client;
  }
}