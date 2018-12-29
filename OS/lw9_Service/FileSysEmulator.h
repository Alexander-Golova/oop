#pragma once

void StartFileSystemEmulator();
void GetFileSystemEmulatorInfo();

bool HandleCommand(const std::string &cmd);
std::string GetActionResultMessage();