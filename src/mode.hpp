#ifndef SINGSANG_MODE_HPP
#define SINGSANG_MODE_HPP

namespace singsang
{
enum class EGuiMode : int
{
    StartupView = 0,  //< Startup view showing the logo
    CategoryView,     //< Pick a category
    SongView,         //< Pick and play song in category
};
}  // namespace singsang

#endif  // SINGSANG_MODE_HPP