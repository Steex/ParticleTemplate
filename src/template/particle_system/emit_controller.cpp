#include "head.h"

#include "emit_controller.h"
#include "fetcher_factory.h"



Particles::EmitController::EmitController(iXml *_xml)
    : active          (false)
    , looped          (false)
    , density_fetcher (nullptr)
    , duration        (1.0f)
    , time            (0.0f)
    , last_time       (0.0f)
    , times           ()
{
    // Load parameters.
    looped    << _xml->getAttribute("looped");
    duration  << _xml->getAttribute("duration");
    density_fetcher = FetcherFactory::create<Float>(_xml->getChild("fetcher_density"));
}



Particles::EmitController::~EmitController()
{
}



void Particles::EmitController::start()
{
    time = 0.0f;
    last_time = 0.0f;
    active = true;
}



void Particles::EmitController::pause()
{
    active = false;
}



void Particles::EmitController::resume()
{
    active = true;
}



USize Particles::EmitController::process(Float _tick)
{
    if (!active)
    {
        return 0;
    }

    Float next_time = time + _tick;
    if (!looped && next_time >= duration)
    {
        next_time = duration;
        active = false;
    }

    Float emit_dencity = density_fetcher->fetch(Math::fmod(time, duration) / duration);
    Float emit_interval = 1.0f / emit_dencity;
    USize emit_count = (USize)((next_time - last_time) / emit_interval);

    if (emit_count > 0)
    {
        if (times.size() < emit_count)
        {
            times.resize(emit_count + 4); // add some extra space to minimize potential reallocations
        }

        if (looped)
        {
            for (USize i = 0; i < emit_count; ++i)
            {
                times[i] = Math::fmod(last_time + emit_interval * (i + 1), duration);
            }
        }
        else
        {
            for (USize i = 0; i < emit_count; ++i)
            {
                times[i] = last_time + emit_interval * i;
            }
        }

        last_time += emit_interval * emit_count;
    }

    time = next_time;

    return emit_count;
}
