#ifndef SINGSANG_HELPERS_HPP
#define SINGSANG_HELPERS_HPP

namespace singsang
{
template <typename T>
T clip(T f_low, T f_value, T f_high)
{
    assert(f_low <= f_high);

    if (f_value < f_low)
    {
        return f_low;
    }
    if (f_value > f_high)
    {
        return f_high;
    }
    return f_value;
}

template <typename InputType, typename OutputType>
class TRangeMapper
{
public:
    TRangeMapper() = delete;

    explicit TRangeMapper(const InputType f_lowIn, const InputType f_highIn,
                          const OutputType f_lowOut, const OutputType f_highOut,
                          const bool f_clipOutput = true)
        : m_lowIn(f_lowIn)
        , m_highIn(f_highIn)
        , m_lowOut(f_lowOut)
        , m_highOut(f_highOut)
        , m_clipOutput(f_clipOutput)
    {
        assert((f_highIn - f_lowIn) > static_cast<InputType>(0.F));
    }

    ~TRangeMapper() = default;

    OutputType operator()(const InputType f_value) const
    {
        const float inputFraction = (f_value - m_lowIn) / (m_highIn - m_lowIn);

        const OutputType valueOut =
            m_lowOut + inputFraction * (m_highOut - m_lowOut);

        if (m_clipOutput)
        {
            return clip<OutputType>(m_lowOut, valueOut, m_highOut);
        }
        else
        {
            return valueOut;
        }
    };

private:
    const InputType  m_lowIn;
    const InputType  m_highIn;
    const OutputType m_lowOut;
    const OutputType m_highOut;
    const bool       m_clipOutput;
};

using CFloatRangeMapper = TRangeMapper<float, float>;

}  // namespace singsang

#endif  // SINGSANG_HELPERS_HPP