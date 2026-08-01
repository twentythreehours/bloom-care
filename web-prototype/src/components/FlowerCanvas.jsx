import { useEffect, useRef } from "react";

const SKETCH_SIZE = 600;

// The sketch has no easing of its own — it redraws straight from whatever
// values currently are, every frame. Since our sensor values only tick every
// couple seconds, calling the setters with raw values makes the flower snap
// between poses/colors. Chasing smoothed values every animation frame instead
// turns that into a continuous glide.
const EASE_PER_FRAME = 0.06;

// Strips the sketch's own debug UI (title, stage tabs, sensor sliders) and
// transparent-izes its dark checkerboard canvas backdrop so it blends into
// our card instead of looking like a separate embedded page.
function declutterSketchDocument(doc) {
  const stageTabs = doc.getElementById("stage-tabs");
  if (stageTabs) stageTabs.style.display = "none";

  const controls = doc.getElementById("controls");
  if (controls) controls.style.display = "none";

  const heading = doc.querySelector("h1");
  if (heading) heading.style.display = "none";

  doc.documentElement.style.background = "transparent";
  doc.body.style.background = "transparent";
  doc.body.style.minHeight = "0";

  const canvasWrap = doc.getElementById("canvas-wrap");
  if (canvasWrap) {
    canvasWrap.style.background = "transparent";
    canvasWrap.style.backgroundImage = "none";
    canvasWrap.style.borderRadius = "0";
  }
}

function easeToward(current, target) {
  return current + (target - current) * EASE_PER_FRAME;
}

function applySensorValues(sketch, values) {
  sketch.setHeartbeat?.(values.heartbeat);
  sketch.setBloodOxygen?.(values.spo2);
  sketch.setSkinTemp?.(values.skinTemp);
  sketch.setActivity?.(values.activity);
}

export default function FlowerCanvas({ src, stage, sensor, size = 320, muted = false }) {
  const iframeRef = useRef(null);
  const targetRef = useRef(sensor);
  const displayedRef = useRef(sensor);

  useEffect(() => {
    targetRef.current = sensor;
  }, [sensor]);

  useEffect(() => {
    iframeRef.current?.contentWindow?.flowerSketch?.setStage?.(stage);
  }, [stage]);

  useEffect(() => {
    let frameId;

    const tick = () => {
      const sketch = iframeRef.current?.contentWindow?.flowerSketch;
      if (sketch) {
        const target = targetRef.current;
        const displayed = displayedRef.current;
        const next = {
          heartbeat: easeToward(displayed.heartbeat, target.heartbeat),
          spo2: easeToward(displayed.spo2, target.spo2),
          skinTemp: easeToward(displayed.skinTemp, target.skinTemp),
          activity: easeToward(displayed.activity, target.activity),
        };
        displayedRef.current = next;
        applySensorValues(sketch, next);
      }
      frameId = requestAnimationFrame(tick);
    };

    frameId = requestAnimationFrame(tick);
    return () => cancelAnimationFrame(frameId);
  }, []);

  const handleLoad = () => {
    const iframe = iframeRef.current;
    if (!iframe) return;
    const doc = iframe.contentDocument;
    if (doc) declutterSketchDocument(doc);
    const sketch = iframe.contentWindow?.flowerSketch;
    if (!sketch) return;
    sketch.setStage?.(stage);
    applySensorValues(sketch, displayedRef.current);
  };

  const scale = size / SKETCH_SIZE;

  return (
    <div
      className={`flower-canvas${muted ? " flower-canvas--muted" : ""}`}
      style={{ width: size, height: size }}
    >
      <iframe
        ref={iframeRef}
        src={src}
        title="Bloom flower"
        width={SKETCH_SIZE}
        height={SKETCH_SIZE}
        scrolling="no"
        style={{ transform: `scale(${scale})` }}
        onLoad={handleLoad}
      />
    </div>
  );
}
