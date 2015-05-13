Ractive.events.menu = function ( node, fire ) {
  var longpressDuration = 500, threshold = 5, contextmenuHandler, touchstartHandler;

  // intercept contextmenu events and suppress them
  contextmenuHandler = function ( event ) {
    event.preventDefault();

    // we'll pass along some coordinates. This will make more sense below
    fire({
      node: node,
      original: event,
      x: event.clientX,
      y: event.clientY
    });
  };

  node.addEventListener( 'contextmenu', contextmenuHandler );

  // that was easy! but touch is a little more complicated
  touchstartHandler = function ( event ) {
    var touches, touch, finger, startX, startY, moveHandler, cancel, timeout;

    // for simplicity, we'll only deal with single finger presses
    if ( event.touches.length !== 1 ) {
      return;
    }

    // suppress the default behaviour
    event.preventDefault();

    // we'll need this info later
    touch = event.touches[0];
    finger = touch.identifier;
    startX = touch.clientX;
    startY = touch.clientY;

    // after the specified delay, fire the event...
    timeout = setTimeout( function () {
      // there is no underlying event we could meaningfully pass on. but
      // we can pass along some coordinates
      fire({
        node: node,
        x: startX,
        y: startY
      });
      cancel();
    }, longpressDuration );

    // ...unless the timeout is cancelled
    cancel = function () {
      clearTimeout( timeout );

      // tidy up after ourselves
      window.removeEventListener( 'touchmove', touchmoveHandler );
      window.removeEventListener( 'touchend', cancel );
      window.removeEventListener( 'touchcancel', cancel );
    };

    // if the user moves their finger, test whether they've moved it beyond a
    // certain threshold or if they've left the target element
    touchmoveHandler = function ( event ) {
      var touch, currentTarget;

      // find the right touch (another finger may have touched the screen)
      i = event.touches.length;
      while ( i-- ) {
        if ( event.touches[i].identifier === finger ) {
          touch = event.touches[i];
          break;
        }
      }

      if ( !touch ) {
        cancel();
        return;
      }

      dx = touch.clientX - startX;
      dy = touch.clientY - startY;
      currentTarget = document.elementFromPoint( touch.clientX, touch.clientY );

      // if the finger has moved too far, or is no longer over the target, cancel
      if ( Math.abs( dx ) > threshold || Math.abs( dy ) > threshold || !el.contains( currentTarget ) ) {
        cancel();
      }
    };

    window.addEventListener( 'touchmove', touchmoveHandler );
    window.addEventListener( 'touchend', cancel );
    window.addEventListener( 'touchcancel', cancel );
  };

  node.addEventListener( 'touchstart', touchstartHandler );

  // return an object with a teardown method, so we can unbind everything when the
  // element is removed from the DOM
  return {
    teardown: function () {
      node.removeEventListener( 'contexmenu', contextmenuHandler );
      node.removeEventListener( 'touchstart', touchstartHandler );
    }
  };
};