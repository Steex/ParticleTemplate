#ifndef _PSYS_EMIT_CONTROLLER_INCLUDED_
#define _PSYS_EMIT_CONTROLLER_INCLUDED_


#include "fetcher.h"


namespace Particles
{
    class EmitController
    {
    public:

        typedef std::vector<Float> TimeList;

        EmitController(iXml *_xml);
        ~EmitController();

        Bool isActive() const { return active; }
        void start();
        void pause();
        void resume();

        USize process(Float _tick);

        Float getDuration() const { return duration; }
        const TimeList& getTimes() const { return times; }

    private:

        Bool active;
        Bool looped;
        Fetcher<Float> *density_fetcher;
        Float duration;
        Float time;
        Float last_time;
        TimeList times; // wrapped by the emit_duration
    };
}


#endif // _PSYS_EMIT_CONTROLLER_INCLUDED_
