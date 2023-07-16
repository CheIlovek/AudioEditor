#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

namespace ProjectColours {
	const Colour textColour{ Colours::white };
	const Colour generalBackground { 0xff131313 };
	namespace Files {
		const Colour headerStartColour{ 0xff111111 };
		const Colour headerEndColour{ 0xff181818 };

		const Colour fileRowBackgroundUnselected{ 0xff303030 };
		const Colour fileRowBackgroundSelected{ 0xff454545 };

		const Colour listBoxBackground{ 0xff242223 };
		const Colour listBoxOutline{ 0 };

		const Colour listBoxNoFileBackground{ 0x40403D3F };
		const Colour listBoxNoFileText{ Colours::white };
	}

	namespace Tracks {

		const Colour filenameBackground{ 0xff302E30 };
		const Colour filenameText{ Colours::white };

		const Colour listBoxBackground{ 0xff242223 };
		const Colour listBoxBackgroundSelected{ 0xff353334 };
		const Colour listBoxOutline{ Colours::black };
		const Colour listBoxNoTracksBackground{ 0x99403D3F };
		const Colour listBoxNoTracksText{ Colours::white };

		const Colour playMarker{ 0xffff002a };

		const Colour selectionArea{ Colours::blue.withAlpha(.2f)};
		const Colour selectionBorders{ Colours::blue };
		const Colour buttonColour{ 0xff363636 };
		const Colour muteButtonActiveColour{ 0xff790a0a };
		const Colour superiorButtonActiveColour{ 0xff154b0a };
		const Colour sliderColour{ 0xff23c1fe };

		namespace Waveform {
			const Colour noLoadFileBackground{ 0xff403D3F };
			const Colour noLoadFileText{ Colours::white };
			const Colour loadFileBackground{ 0xff121011 };
			const Array<Colour> waveformBrushes = { 
				Colour(0xff25c1ff),
				Colour(0xff25ff70),
				Colour(0xffffea25),
				Colour(0xffff7e25)
			};
		}
	}

	namespace EffectHistory {
		const Colour headerStartColour{ 0xff111111 };
		const Colour headerEndColour{ 0xff181818 };

		const Colour rowBackground{ 0xff303030 };
		const Colour listBoxBackground{ 0xff242223 };
		const Colour listBoxOutline{ 0 };
		const Colour comboBoxOutline{ Colours::grey };
		const Colour comboBoxFocusedOutline{ Colours::white };
		const Colour buttonColour{ 0xff363636 };
		const Colour buttonOnColour{ buttonColour.brighter()};
		const Colour comboBoxbackgroundColour{ 0xff131313 };
	}

	namespace DialogWindow {
		const Colour dialogWindowBackground{ 0xff303030 };
		const Colour buttonColour{ 0xffe9e9e9 };
		const Colour buttonOnColour{ Colours::grey };
		const Colour buttonTextColour{ 0xff131313 };
		const Colour sliderColour{ 0xff23c1fe };
	}

	namespace Playback {
		namespace PlayButton {
			const Colour startColour{ 0xff479aff };
			const Colour endColour{ 0xff3877aa };
		}

		namespace Timer {
			const Colour boxOutline{ Colours::black };
			const Colour boxBackground{ 0xff1f1f1f };
			const Colour text{ 0xff62a5fc };
		}
		
	}

	namespace VolumeSlider {
		const Colour background{ 0xff363435 };
		
		const Colour startColour{ Colours::green };
		const Colour middleColour{ Colours::yellow };
		const Colour endColour{ Colours::red };
	}

}
