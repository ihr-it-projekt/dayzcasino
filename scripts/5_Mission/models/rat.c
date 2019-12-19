class Rat {
    ref array <int> positions;
    float quote;
    int number
	ImageWidget ratImage;
	bool isAnimationFinished = false;
	bool hasPassGoal = false;

    void Rat(int startPos, int startNumber) {
        positions = new array<int>;
        positions.Insert(startPos);
        quote = Math.RandomIntInclusive(10, 50) / 10;
        number = startNumber;
    }

    int GetLastPosition() {
        return positions.Get(positions.Count() - 1);
    }

    void AddStep(int stepPos) {
        this.positions.Insert(stepPos);
    }
	
	void SetImageWidget(ImageWidget image) {
		ratImage = image;
	}
	
	void GoToStep(int index) {
		if (ratImage) {
			if (positions.IsValidIndex(index) + DAYZ_CASINO_ANIMATE_STEPS_AFTER_GOAL_RATE_RACE) {
                hasPassGoal = true;
			} else if (positions.IsValidIndex(index)) {
				int pos = positions.Get(index);

				ratImage.SetPos(pos, 13.25);
			} else {
				isAnimationFinished = true;
			}
		} else {
			DebugMessageCasino("Has no image");
		}
	}
};