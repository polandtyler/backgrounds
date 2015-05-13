var tooltipDecorator = function ( node, content ) {
    var tooltip = $(node);
    tooltip.tooltip();
    tooltip.data('bs.tooltip').options.title = tooltip.attr("data-title");
    // console.log('Creating tooltip '+tooltip.attr("data-title"));
    return {
        teardown: function () {
        	// console.log('tearing down '+tooltip.attr('data-title'));
        	tooltip.tooltip('destroy');
        }
    }
};

Ractive.decorators.tooltip = tooltipDecorator;
