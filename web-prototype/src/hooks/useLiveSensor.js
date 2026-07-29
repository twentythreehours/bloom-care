import { useEffect, useRef, useState } from "react";
import { createInitialSample, nextSample } from "../sensor/mockSensorDataSource";
import { summarize } from "../sensor/dailyDataService";
import { mapToFlowerParameters } from "../sensor/flowerMapper";

const SAMPLE_INTERVAL_MS = 2000;
const MAX_BUFFERED_SAMPLES = 300;

export function useLiveSensor(connected) {
  const [latest, setLatest] = useState(() => createInitialSample());
  const samplesRef = useRef([latest]);
  const [summary, setSummary] = useState(() => summarize(samplesRef.current));

  useEffect(() => {
    if (!connected) return undefined;

    const id = setInterval(() => {
      setLatest((previous) => {
        const sample = nextSample(previous);
        const buffer = [...samplesRef.current, sample].slice(-MAX_BUFFERED_SAMPLES);
        samplesRef.current = buffer;
        setSummary(summarize(buffer));
        return sample;
      });
    }, SAMPLE_INTERVAL_MS);

    return () => clearInterval(id);
  }, [connected]);

  const flowerParameters = summary ? mapToFlowerParameters(summary) : null;

  return { latest, summary, flowerParameters };
}
