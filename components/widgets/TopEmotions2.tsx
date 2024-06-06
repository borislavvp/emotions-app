import { useEffect, useState } from "react";
import { Emotion, EmotionName } from "../../lib/data/emotion";

type TopEmotionsProps = {
  className?: string;
  emotions: Emotion[];
  numEmotions: number;
};


const MAIN_EMOTIONS = ["FEAR", "ANGER", "SADNESS", "JOY", "SURPRISE"] as const

const EMOTIONS_GROUP = {
  FEAR:[
    "Fear",
    "Anxiety",
    "Horror",
    "Surprise",
    "Doubt"
  ]as EmotionName[],
  ANGER:[
    "Anger",
    "Contempt",
    "Frustration",
    "Envy",
    "Disgust"
  ]as EmotionName[],
  SADNESS:[
    "Distress",
    "Pain",
    "Sadness",
    "Guilt",
    "Shame",
    "Disappointment",
    "Nostalgia",
    //NOT SURE
    "Embarrassment",
    "Boredom",
    "Empathic Pain",
    "Tiredness",
  ]as EmotionName[],
  JOY:[
    "Excitement",
    "Amusement",
    "Joy",
    "Surprise",
    "Ecstasy",
    "Love",
    "Adoration",
    "Romance",
    "Satisfaction",
    "Relief",
    "Triumph",
    "Contentment",
    "Aesthetic Appreciation",
    "Desire",
    "Interest",
    "Calmness",
    "Craving",
    "Determination",
    "Concentration"
  ]as EmotionName[],
  SURPRISE:[
    "Awe",
    "Contemplation",
    "Sympathy",
    "Realization",
    "Confusion"
  ] as EmotionName[]
} 

const getEmotionPercentage = (mainEmotion:typeof MAIN_EMOTIONS[number],emotions: Emotion[]) => {
  let score = 0;
  emotions
  .sort((a: Emotion, b: Emotion) => b.score - a.score)
  .slice(0, 3).forEach(emotion => {
    if(EMOTIONS_GROUP[mainEmotion].includes(emotion.name)){
      score+= emotion.score;
    }
  })
  return score;
}

const getTopEmotion = (emotions: Emotion[]) => {
  let highestScore = -1;
  let chosenEmotion:string = MAIN_EMOTIONS[0]
  MAIN_EMOTIONS.forEach(mainEm => {
    const score = getEmotionPercentage(mainEm,emotions);
    if(score > highestScore){
      highestScore = score;
      chosenEmotion = mainEm;
    }
  })

  switch(chosenEmotion){
    case "FEAR":
      return "/fear.png"
    case "SADNESS":
      return "/sadness.png"
    case "ANGER":
      return "/anger.png"
    case "JOY":
      return "/joy.png"
    case "SURPRISE":
      return "/surprise.png"
  }
  return chosenEmotion;
}
export function TopEmotions({ className, emotions, numEmotions }: TopEmotionsProps) {
  className = className || "";
  const [topEmotion, setTopEmotion] = useState(""); // Store the function result

  // Update result whenever the prop changes
  useEffect(() => {
    console.log(
      emotions.sort((a: Emotion, b: Emotion) => b.score - a.score)
      )
    const newResult = getTopEmotion(emotions);
    setTopEmotion(newResult);
  }, [emotions]); // Dependency array ensures update on prop change

  console.log(getTopEmotion(emotions))
  return (
    <div className={`${className}`}>
      <div className="mb-3 flex rounded-full  text-sm ">
        {topEmotion !== "" && emotions.length > 0 && <div>
          <img src={topEmotion} alt="logo" width={200} />
        </div>}
      </div>
    </div>
  );
}

TopEmotions.defaultProps = {
  numEmotions: 3,
};
