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

// TODO: CvEnumSerialization.h (remaining SDK enum stream declarations).

#endif // INCLUDED_CvEnumSerialization_H