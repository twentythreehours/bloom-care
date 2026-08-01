import { useRef, useState } from "react";
import FlowerCanvas from "./FlowerCanvas";
import { ShareIcon, HeartIcon, MoonIcon, GlowIcon, MoodFaceIcon } from "./icons";
import { getSimulatedDayData, formatSleep } from "../flowerHistory";
import { isSameDay, TODAY } from "../cycleData";
import { FLOWER_CYCLE_SRC } from "../flowerAssets";

const CARD_WIDTH = 640;
const CARD_HEIGHT = 800;

function loadImage(src) {
  return new Promise((resolve, reject) => {
    const img = new Image();
    img.onload = () => resolve(img);
    img.onerror = reject;
    img.src = src;
  });
}

async function buildShareImage({ flowerDataUrl, flowerName, dateLabel, phaseName }) {
  const img = await loadImage(flowerDataUrl);

  const canvas = document.createElement("canvas");
  canvas.width = CARD_WIDTH;
  canvas.height = CARD_HEIGHT;
  const ctx = canvas.getContext("2d");

  ctx.fillStyle = "#f4f0ea";
  ctx.fillRect(0, 0, CARD_WIDTH, CARD_HEIGHT);

  const flowerSize = 440;
  const offsetX = (CARD_WIDTH - flowerSize) / 2;
  const offsetY = 90;
  ctx.drawImage(img, 0, 0, img.width, img.height, offsetX, offsetY, flowerSize, flowerSize);

  ctx.textAlign = "center";
  ctx.fillStyle = "#2c2834";
  ctx.font = "600 34px -apple-system, 'Segoe UI', sans-serif";
  ctx.fillText(flowerName, CARD_WIDTH / 2, offsetY + flowerSize + 66);

  ctx.fillStyle = "#8b8898";
  ctx.font = "400 20px -apple-system, 'Segoe UI', sans-serif";
  ctx.fillText(dateLabel, CARD_WIDTH / 2, offsetY + flowerSize + 102);

  ctx.fillStyle = "#7958c8";
  ctx.font = "700 15px -apple-system, 'Segoe UI', sans-serif";
  ctx.fillText(`${phaseName.toUpperCase()} PHASE`, CARD_WIDTH / 2, offsetY + flowerSize + 136);

  ctx.fillStyle = "#c9c4d0";
  ctx.font = "400 13px -apple-system, sans-serif";
  ctx.fillText("Bloom", CARD_WIDTH / 2, CARD_HEIGHT - 30);

  return new Promise((resolve) => canvas.toBlob(resolve, "image/png"));
}

export default function DayDetailModal({ date, onClose }) {
  const flowerWrapRef = useRef(null);
  const [shareState, setShareState] = useState("idle"); // idle | working | done | error

  const data = getSimulatedDayData(date);
  const dateLabel = date.toLocaleDateString("en-US", {
    weekday: "long",
    month: "long",
    day: "numeric",
    year: "numeric",
  });
  const isToday = isSameDay(date, TODAY);

  async function handleShare() {
    const iframe = flowerWrapRef.current?.querySelector("iframe");
    const canvas = iframe?.contentDocument?.querySelector("canvas");
    if (!canvas) {
      setShareState("error");
      setTimeout(() => setShareState("idle"), 1800);
      return;
    }

    setShareState("working");
    try {
      const flowerDataUrl = canvas.toDataURL("image/png");
      const blob = await buildShareImage({
        flowerDataUrl,
        flowerName: data.flowerName,
        dateLabel,
        phaseName: data.phase.name,
      });
      const file = new File([blob], `bloom-${date.toISOString().slice(0, 10)}.png`, {
        type: "image/png",
      });

      if (navigator.canShare?.({ files: [file] })) {
        await navigator.share({
          files: [file],
          title: data.flowerName,
          text: `${data.flowerName} · ${dateLabel}`,
        });
      } else {
        const url = URL.createObjectURL(blob);
        const a = document.createElement("a");
        a.href = url;
        a.download = file.name;
        document.body.appendChild(a);
        a.click();
        a.remove();
        URL.revokeObjectURL(url);
      }
      setShareState("done");
    } catch (err) {
      setShareState(err?.name === "AbortError" ? "idle" : "error");
      setTimeout(() => setShareState("idle"), 1800);
      return;
    }
    setTimeout(() => setShareState("idle"), 1800);
  }

  const shareLabel = {
    idle: "Share",
    working: "Preparing…",
    done: "Shared",
    error: "Couldn't share",
  }[shareState];

  return (
    <div className="day-modal-backdrop" onClick={onClose}>
      <div className="day-modal" onClick={(e) => e.stopPropagation()}>
        <button
          type="button"
          className="day-modal__close"
          onClick={onClose}
          aria-label="Close"
        >
          ×
        </button>

        <div className="day-modal__flower" ref={flowerWrapRef}>
          <FlowerCanvas
            src={FLOWER_CYCLE_SRC}
            stage={data.phase.id}
            sensor={data.sensor}
            size={220}
          />
        </div>

        <h1 className="day-modal__name">{data.flowerName}</h1>
        <p className="day-modal__date">
          {dateLabel}
          {isToday ? " · Today" : ""}
        </p>
        <span className="day-modal__phase">
          {data.phase.name} Phase · Cycle Day {data.cycleDay}
        </span>

        <div className="stats-pill day-modal__stats">
          <span className="stats-pill__item">
            <HeartIcon size={12} color="var(--color-primary)" />
            {data.bpmDisplay} bpm
          </span>
          <span className="stats-pill__divider" />
          <span className="stats-pill__item">
            <MoonIcon size={12} color="var(--color-primary)" />
            {formatSleep(data.sleepMinutes)}
          </span>
          <span className="stats-pill__divider" />
          <span className="stats-pill__item">
            <GlowIcon size={12} color="var(--color-primary)" />
            {data.glow}% Oxygen
          </span>
        </div>

        <div className="day-modal__log">
          <MoodFaceIcon size={20} variant={data.mood} color="var(--color-primary)" />
          <p className="day-modal__log-text">“{data.journal}”</p>
        </div>

        <button
          type="button"
          className="day-modal__share"
          onClick={handleShare}
          disabled={shareState === "working"}
        >
          <ShareIcon size={16} color="#fff" />
          {shareLabel}
        </button>
      </div>
    </div>
  );
}
