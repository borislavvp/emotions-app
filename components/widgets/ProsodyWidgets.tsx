import { AudioWidgets } from "./AudioWidgets";

export function ProsodyWidgets() {
  return (
    <div>
      <AudioWidgets modelName="prosody" recordingLengthMs={2000} streamWindowLengthMs={5000} />
    </div>
  );
}
