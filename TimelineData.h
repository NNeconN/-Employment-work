#pragma once

class Timeline
{
public:
	Timeline();
	void TrackData(); //タイムライン上のトラック情報 タイムライン上でのファイルデータ読み込みなど

	void Demo_TimelineGraph();
	bool addButton2; //トラック追加ボタン

private:
	bool addButton; //トラック追加ボタン

	double frametime;
};