import { useState } from "react";
import TodayPage from "./components/TodayPage";
import CalendarPage from "./components/CalendarPage";
import ProfilePage from "./components/ProfilePage";
import BottomNav from "./components/BottomNav";
import "./App.css";

function App() {
  const [activeTab, setActiveTab] = useState("today");
  const [mood, setMood] = useState(null);
  const [journal, setJournal] = useState("");

  return (
    <div className="phone-frame">
      <div className="status-bar">
        <span>9:41</span>
        <span className="status-bar__icons">●●●</span>
      </div>

      <main className="phone-screen">
        {activeTab === "today" && (
          <TodayPage
            dayCount={1}
            mood={mood}
            onSelectMood={setMood}
            journal={journal}
            onJournalChange={setJournal}
          />
        )}
        {activeTab === "calendar" && <CalendarPage />}
        {activeTab === "profile" && <ProfilePage />}
      </main>

      <BottomNav active={activeTab} onChange={setActiveTab} />
    </div>
  );
}

export default App;
