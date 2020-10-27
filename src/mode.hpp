#ifndef SINGSANG_MODE_HPP
#define SINGSANG_MODE_HPP

namespace singsang
{
enum class EGuiMode : int32_t
{
    StartupView,   //< Startup view showing the logo
    CategoryView,  //< Pick a category
    SongView,      //< Pick and play song in category
};
}  // namespace singsang

#endif  // SINGSANG_MODE_HPP