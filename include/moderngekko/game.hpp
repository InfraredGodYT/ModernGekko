#pragma once

#include <cstdint>
#include <filesystem>
#include <optional>
#include <string>

namespace moderngekko
{
enum class GamePlatform
{
  GameCube,
  Wii,
};

struct GameMetadata
{
  std::filesystem::path root;
  std::filesystem::path main_dol;
  std::filesystem::path main_rel;
  std::string game_name;
  std::string disc_id;
  GamePlatform platform = GamePlatform::GameCube;
  std::uint32_t entry_point = 0;
  std::string dol_sha256;
  std::string rel_sha256;
  std::string assets_sha256;
};

struct GameInspectResult
{
  std::optional<GameMetadata> metadata;
  std::string error;

  explicit operator bool() const { return metadata.has_value(); }
};

// hash_assets: also compute assets_sha256, a SHA-256 over every file under
// files/. That reads the whole disc (over a gigabyte for many games), so only
// callers that compare it -- netplay compatibility and builds pinned with
// MODERNGEKKO_REQUIRED_ASSETS_SHA256 -- ask for it; otherwise it stays empty.
GameInspectResult InspectGame(const std::filesystem::path& root, bool hash_assets = false);
std::optional<std::string> HashFileSha256(const std::filesystem::path& path);
std::optional<std::string> HashDirectorySha256(const std::filesystem::path& root);
}  // namespace moderngekko

namespace ModernGekko = moderngekko;
