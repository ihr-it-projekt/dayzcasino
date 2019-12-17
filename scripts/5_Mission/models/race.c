class Race{

    ref array<ref Rat> rats;
    ref Rat winRat;
	bool isAnimationFinished = false;

    void Race(int ratCount) {
        rats = new array<ref Rat>;
        for(int x; x < ratCount; x++) {
            ref Rat rat = new Rat(178, x + 1);
        }
    }

    void CreateRaceResults() {
		if (!GetGame().IsServer()){
			return;
		}
		
        bool isLastStep = false;

        while (!isLastStep) {
            isLastStep = true;
            foreach(int i, Rat rat: rats) {
                int newPos = rat.GetLastPosition() + Math.RandomIntInclusive(1, 2);

                if (DAYZ_CASINO_DEBUG && i == 0) {
                    newPos = 2;
                }

                if (DAYZ_CASINO_RAT_RACE_GOAL_LINE <= newPos) {
                    if (null == winRat) {
                        winRat = rat;
                    }
                    rat.AddStep(DAYZ_CASINO_RAT_RACE_GOAL_LINE);
                } else {
                    rat.AddStep(newPos);
                    isLastStep = false;
                }
            }
        }
    }
	
	void AnimateRace(int step) {
		bool isFinished = true;
		foreach(int i, Rat rat: rats) {
			rat.GoToStep(step);
			isAnimationFinished = isFinished && rat.isAnimationFinished;
		}
	}
	
	
};