var WelcomeView = new function () {
	var self = this;

	this.setTemplate = function (template) {
		if (template)
		{
			self.template = template;
		}
	}

	this.Initialize = function() {
		self.ra = new Ractive({
			el: "WelcomeView-container",
			template: self.template,
			data: {
				currentPage: 0,
				ResourceManager: ResourceManager,
				Main: Main.ra,
				Utils: Utils,
				isCarouselInitialized: false
			}
		});
		self.ra.on("closeWelcomeViewClicked", function (evt) {
			self.ra.set("Main.shouldShowWelcomeView", false);
		});
		self.ra.on("nextWelcomeViewClicked", function (evt) {
			if (self.ra.get("currentPage") < $('.carousel .item').length-1) {
				$('.carousel').carousel("next");
			}
			else
				self.ra.fire("closeWelcomeViewClicked");
		});

		self.ra.observe("Main.shouldShowWelcomeView", function (newVal, oldVal) {
			if (newVal && !oldVal) {
				self.ra.set("isCarouselInitialized", false);
			}
		})
	}

	this._initializeCarouselIfNeeded = function () {
		if (!self.ra.get("isCarouselInitialized")) {
			$('.carousel').on('slid.bs.carousel', function () {
			  var index = $('.carousel .active').index('.carousel .item')
			  self.ra.set("currentPage", index);
			})
			self.ra.toggle("isCarouselInitialized");
		}
	}
}

