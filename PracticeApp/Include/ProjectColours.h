#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

namespace ProjectColours {
	const Colour textColour{ Colours::white };
	const Colour generalBackground { 0xff131313 };
	namespace Files {
		const Colour fileRowBackgroundUnselected{ 0xff303030 };
		const Colour fileRowBackgroundSelected{ Colours::grey };
		const Colour listBoxBackground{ 0xff242223 };
		const Colour listBoxOutline{ Colours::black };
	}

	namespace Tracks {

		const Colour listBoxBackground{ 0xff242223 };
		const Colour listBoxOutline{ Colours::black };
		const Colour playMarker{ Colours::green };

		const Colour selectionArea{ Colours::blue.withAlpha(.2f)};
		const Colour selectionBorders{ Colours::blue };
		const Colour buttonColour{ 0xff363636 };
		const Colour sliderColour{ 0xff23c1fe };

		namespace Waveform {
			const Colour noLoadFileBackground{ Colours::white };
			const Colour noLoadFileText{ Colours::darkgrey };
			const Colour loadFileBackground{ 0xff121011 };
			const Colour brush{ 0xff25c1fe };
		}
	}

	namespace DialogWindow {
		const Colour dialogWindowBackground{ 0xff303030 };
		const Colour buttonColour{ Colours::grey };
		const Colour buttonOnColour{ Colours::lightgrey };
		const Colour buttonTextColour{ 0xff131313 };
		const Colour sliderColour{ 0xff23c1fe };
	}

	namespace Playback {
		namespace PlayButton {
			const Colour startColour{ 0xff479aff };
			const Colour endColour{ 0xff3877aa };
		}
		
	}

	namespace VolumeSlider {
		const Colour background{ 0xff363435 };
		
		const Colour startColour{ Colours::green };
		const Colour middleColour{ Colours::yellow };
		const Colour endColour{ Colours::red };
	}

}
