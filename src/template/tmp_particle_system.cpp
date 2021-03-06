#include "head.h"

#include "tmp_particle_system.h"
#include "particle_system/static/emit_controller.h"


/*PLACEHOLDER_CURVES_DATA*/
static const USize proc_sot_scales_size = 64;
static const Float proc_sot_scales_table[] = {
    0.000000f, 0.267412f, 0.468346f, 0.628770f, 0.759640f, 0.855612f, 0.926800f, 0.975766f,
    0.996625f, 0.988054f, 0.956685f, 0.915066f, 0.870118f, 0.824470f, 0.779587f, 0.736140f,
    0.694287f, 0.654101f, 0.616448f, 0.580103f, 0.545601f, 0.513075f, 0.481582f, 0.452396f,
    0.423919f, 0.397477f, 0.371977f, 0.347643f, 0.325048f, 0.302453f, 0.282410f, 0.262627f,
    0.243357f, 0.226282f, 0.209206f, 0.192745f, 0.178266f, 0.163788f, 0.149400f, 0.137405f,
    0.125410f, 0.113416f, 0.102790f, 0.093167f, 0.083543f, 0.073919f, 0.066214f, 0.058851f,
    0.051487f, 0.044124f, 0.038565f, 0.033355f, 0.028145f, 0.022936f, 0.018821f, 0.015661f,
    0.012502f, 0.009342f, 0.006183f, 0.004829f, 0.003622f, 0.002415f, 0.001207f, 0.000000f };


GeneratedParticles::TempSparkles::TempSparkles(iXml *_xml)
    : emit_controller (nullptr)
    , max_particles   (1000)
    , particle_count  (0)
    , particle_data   (nullptr)
    , create_acc      (0.0f)
/*PLACEHOLDER_PROCESSORS_DATA_INIT*/
    , proc_accel_acceleraton (0.0f, 100.0f)
{
    // Create an emit controller.
    emit_controller = new EmitController(_xml->getChild("emit_controller"));

    // Allocate particle data.
    particle_data = new ParticleParams[max_particles];
}



GeneratedParticles::TempSparkles::~TempSparkles()
{
    // Release the particle data.
    delete[] particle_data;
}



Bool GeneratedParticles::TempSparkles::isActive() const
{
    return emit_controller->isActive();
}



void GeneratedParticles::TempSparkles::start()
{
    emit_controller->start();
}



void GeneratedParticles::TempSparkles::pause()
{
    emit_controller->pause();
}



void GeneratedParticles::TempSparkles::resume()
{
    emit_controller->resume();
}



void GeneratedParticles::TempSparkles::update(Float _tick)
{
    // Process existing particles.
    if (particle_count > 0)
    {
        ParticleParams *last_particle = particle_data + (particle_count - 1);

        // Update particles.
        for (ParticleParams *particle = particle_data; particle <= last_particle; ++particle)
        {
/*PLACEHOLDER_UPDATE*/
            particle->age += _tick;
            particle->dead = particle->dead || particle->age >= particle->lifetime;

            particle->angle += particle->rot_speed * _tick;

            particle->position += particle->velocity * _tick;
            particle->velocity += proc_accel_acceleraton * _tick;

            particle->scale = fetchCurve(particle->age / particle->lifetime, proc_sot_scales_table, proc_sot_scales_size);
        }

        // Clean dead particles.
        ParticleParams *dest_particle = particle_data;

        for (ParticleParams *particle = particle_data; particle <= last_particle; ++particle)
        {
            if (!particle->dead)
            {
                memcpy(dest_particle++, particle, sizeof(ParticleParams));
            }
        }

        // Update the particle count.
        particle_count = dest_particle - particle_data;
    }

    // Emit new particles.
    USize emit_count = emit_controller->process(_tick);
    if (emit_count > 0)
    {
        // Zero the particles data (including the 'dead' field).
        memset(particle_data + particle_count, 0, sizeof(ParticleParams) * emit_count);

        ParticleParams *first_particle = particle_data + particle_count;
        ParticleParams *last_particle = first_particle + (emit_count - 1);

        // Init new particles.
        Float emit_duration = emit_controller->getDuration();
        const Float *emit_time = &emit_controller->getTimes().front();

        for (ParticleParams *particle = first_particle; particle <= last_particle; ++particle, ++emit_time)
        {
            Float norm_emit_time = *emit_time / emit_duration;

/*PLACEHOLDER_INIT*/
            particle->position = Rect(-100.0f, -100.0f, 100.0f, 100.0f).getRandomPoint();
            particle->scale = Math::random(0.8f, 1.2f);
            particle->angle = Math::random(Math::TWO_PI);
            particle->color = Color(Math::random(), Math::random(), Math::random());

            particle->age      = 0.0f;
            particle->lifetime = Math::random(1.0f, 2.0f);

            particle->rot_speed = Math::random(-Math::PI, Math::PI);

            Float angle = -Math::HALF_PI + Math::random(-Math::PI * 0.2f, Math::PI * 0.2f);
            Float speed = Math::random(100.0f, 200.0f);
            particle->velocity.x = Math::cos(angle) * speed;
            particle->velocity.y = Math::sin(angle) * speed;

            particle->scale = fetchCurve(norm_emit_time, proc_sot_scales_table, proc_sot_scales_size);
        }

        // Update the particle count.
        particle_count += emit_count;
    }
}



void GeneratedParticles::TempSparkles::render(IRenderer *_renderer) const
{
    _renderer->iterate((const Byte*)particle_data, sizeof(ParticleParams), particle_count);
}
