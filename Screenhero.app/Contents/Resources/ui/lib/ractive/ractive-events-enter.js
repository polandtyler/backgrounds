/*

  Ractive-events-enter
  ====================

  Version 0.1.0.

  The enter event provides a convenient way to trigger behaviours
  when the user's mouse enters or leaves an element.

  The `event` object passed to handlers has a `enter` property which
  is `true` on keydown, `false` on mouseleave. (The keydown and
  mouseleave events are proprietary Internet Explorer events, which
  behave slightly differently to mouseover and mouseout. This plugin
  simulates those events in other browsers.

  Be aware that heavy use of enter interactions is generally considered
  an anti-pattern, since it excludes mobile and tablet users.

  ==========================

  Troubleshooting: If you're using a module system in your app (AMD or
  something more nodey) then you may need to change the paths below,
  where it says `require( 'ractive' )` or `define([ 'Ractive' ]...)`.

  ==========================

  Usage: Include this file on your page below Ractive, e.g:

      <script src='lib/Ractive.js'></script>
      <script src='lib/Ractive-events-enter.js'></script>

  Or, if you're using a module loader, require this module:

      // requiring the plugin will 'activate' it - no need to use
      // the return value
      require( 'Ractive-events-enter' );

  Add a enter event in the normal fashion:

      <div on-enter='foo'>enter over me!</div>

  Then add a handler:

      ractive.on( 'foo', function ( event ) {
        alert( event.enter ); // true on enter, false on leave
      });

*/

(function ( global, factory ) {

  'use strict';

  // Common JS (i.e. browserify) environment
  if ( typeof module !== 'undefined' && module.exports && typeof require === 'function' ) {
    factory( require( 'ractive' ) );
  }

  // AMD?
  else if ( typeof define === 'function' && define.amd ) {
    define([ 'Ractive' ], factory );
  }

  // browser global
  else if ( global.Ractive ) {
    factory( global.Ractive );
  }

  else {
    throw new Error( 'Could not find Ractive! It must be loaded before the Ractive-events-enter plugin' );
  }

}( typeof window !== 'undefined' ? window : this, function ( Ractive ) {

  'use strict';

  var enter, testDiv;

  if ( typeof document === 'undefined' ) {
    // lolz
    return;
  }

  testDiv = document.createElement( 'div' );

  // If we're in IE, we can use native keydown/mouseleave events
  if ( testDiv.onkeydown !== undefined ) {
    enter = function ( node, fire ) {
      var keydownHandler, mouseleaveHandler;

      keydownHandler = function ( event ) {
        if ( event.keyCode == 13 )
          fire({
            node: node,
            original: event
          });
      };

      node.addEventListener( 'keydown', keydownHandler, false );

      return {
        teardown: function () {
          node.removeEventListener( 'keydown', keydownHandler, false );
        }
      };
    };
  }

  else {
    enter = function ( node, fire ) {
      var keydownHandler;

      keydownHandler = function ( event ) {
        if ( node.contains( event.relatedTarget ) ) {
          return;
        }

        if ( event.keyCode == 13 )
          fire({
            node: node,
            original: event
          });
      };

      node.addEventListener( 'keydown', keydownHandler, false );

      return {
        teardown: function () {
          node.removeEventListener( 'keydown', keydownHandler, false );
        }
      };
    };
  }

  Ractive.events.enter = enter;

}));