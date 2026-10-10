#ifndef INCLUDED_CvEnumSerialization_H
#define INCLUDED_CvEnumSerialization_H

FDataStream & operator<<(FDataStream &, const PlayerTypes &);
FDataStream & operator>>(FDataStream &, PlayerTypes &);

FDataStream & operator<<(FDataStream &, const ReplayMessageTypes &);
FDataStream & operator>>(FDataStream &, ReplayMessageTypes &);

FDataStream & operator<<(FDataStream &, const ButtonPopupTypes &);
FDataStream & operator>>(FDataStream &, ButtonPopupTypes &);

FDataStream & operator<<(FDataStream &, const SlotStatus &);
FDataStream & operator>>(FDataStream &, SlotStatus &);

FDataStream & operator<<(FDataStream &, const StorageLocation &);
FDataStream & operator>>(FDataStream &, StorageLocation &);
FDataStream & operator<<(FDataStream &, const WorldSizeTypes &);
FDataStream & operator>>(FDataStream &, WorldSizeTypes &);
FDataStream & operator<<(FDataStream &, const ClimateTypes &);
FDataStream & operator>>(FDataStream &, ClimateTypes &);
FDataStream & operator<<(FDataStream &, const SeaLevelTypes &);
FDataStream & operator>>(FDataStream &, SeaLevelTypes &);
FDataStream & operator<<(FDataStream &, const EraTypes &);
FDataStream & operator>>(FDataStream &, EraTypes &);
FDataStream & operator<<(FDataStream &, const PlanetTypes &);
FDataStream & operator>>(FDataStream &, PlanetTypes &);
FDataStream & operator<<(FDataStream &, const CalendarTypes &);
FDataStream & operator>>(FDataStream &, CalendarTypes &);
FDataStream & operator<<(FDataStream &, const GameSpeedTypes &);
FDataStream & operator>>(FDataStream &, GameSpeedTypes &);
FDataStream & operator<<(FDataStream &, const TurnTimerTypes &);
FDataStream & operator>>(FDataStream &, TurnTimerTypes &);
FDataStream & operator<<(FDataStream &, const GameMode &);
FDataStream & operator>>(FDataStream &, GameMode &);

// TODO: CvEnumSerialization.h (remaining SDK enum stream declarations).

#endif // INCLUDED_CvEnumSerialization_H