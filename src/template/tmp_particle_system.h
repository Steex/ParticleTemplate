#ifndef _PSYS_TEMP_SPARKLES_INCLUDED_
#define _PSYS_TEMP_SPARKLES_INCLUDED_


namespace GeneratedParticles
{
    struct BaseParticleParams
    {
        Bool    dead;
        Vector2 position;
        Float   scale;
        Float   angle;
        Color   color;
    };


    template<typename T>
    T fetchCurve(Float _arg, const T *_table, USize _table_size)
    {
        if (_arg <= 0.0f)
        {
            return _table[0];
        }
        else if (_arg >= 1.0f)
        {
            return _table[_table_size - 1];
        }
        else
        {
            Float soft_index = _arg * (_table_size - 1);
            USize i = (USize)Math::floor(soft_index);
            USize j = (USize)Math::ceil(soft_index);
            Float lerp_coeff = (soft_index - (Float)i);
            return Math::lerp(_table[i], _table[j], lerp_coeff);
        }
    }


    class IRenderer
    {
    public:

        virtual void iterate(const Byte *_start, USize _stride, USize _count) = 0;

    };


    class IParticleSystem
    {
    public:
        virtual void update(Float _tick) = 0;
        virtual void render(IRenderer *_renderer) const = 0;

        virtual USize getMaxCount() const = 0;

    protected:
        ~IParticleSystem() {}
    };


    class TempSparkles: public IParticleSystem
    {
    public:

        TempSparkles();
        virtual ~TempSparkles();

        virtual void update(Float _tick);
        virtual void render(IRenderer *_renderer) const;

        virtual USize getMaxCount() const { return max_particles; }

    private:

        struct ParticleParams: BaseParticleParams
        {
/*PLACEHOLDER_PARTICLE_PARAMS*/
            Float age;
            Float lifetime;
            Float rot_speed;
            Vector2 velocity;
        };


        //Emitter *emitter;
        USize max_particles;
        USize particle_count;
        ParticleParams *particle_data;
        Float create_acc;

/*PLACEHOLDER_PROCESSORS_DATA*/
        Vector2 proc_accel_acceleraton;
    };
}


#endif // _PSYS_TEMP_SPARKLES_INCLUDED_
