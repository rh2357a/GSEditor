#include "pokegold.h"
#include "utils.h"
#include <filesystem>

std::vector<uint8_t> pokegold::build()
{
    const auto base_path = workspace_path / "base.bin";
    const auto target_path = workspace_path / "target.bin";

    debug_log("pokegold::build", "cleanup (path=\"{}\")", workspace_path.string());
    std::filesystem::remove_all(workspace_path);
    std::filesystem::create_directories(workspace_path);

    debug_log("pokegold::build", "copy baserom to workspace dir");
    utils::files::write_bytes_to_file(base_path, rom.data());

    const auto result = utils::files::read_bytes_from_file(target_path);

    // cleanup
#ifdef RELEASE
    std::filesystem::remove_all(workspace_path);
    std::filesystem::create_directories(workspace_path);
#endif

    return result;
}
