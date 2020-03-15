#include "DefaultPathsToIgnoreReader.h"

#include <iostream>

#include "utils/StringHelper.h"
#include "utils/exceptions/FileNotFound.h"

namespace lineCounter
{

DefaultPathsToIgnoreReader::DefaultPathsToIgnoreReader(std::shared_ptr<utils::FileAccess> fileAccessInit)
    : fileAccess{std::move(fileAccessInit)}
{
}

PathsToIgnore DefaultPathsToIgnoreReader::readPathsToIgnore(const std::string& filePath) const
{
    if (const auto fileContent = readFileContainingIgnoredPaths(filePath))
    {
        return utils::getSplitLines(*fileContent);
    }
    return {};
}

boost::optional<std::string>
DefaultPathsToIgnoreReader::readFileContainingIgnoredPaths(const std::string& filePath) const
{
    try
    {
        return fileAccess->readContent(filePath);
    }
    catch (const utils::exceptions::FileNotFound& e)
    {
        std::cerr << "Error while reading ignored paths:" << e.what();
        return boost::none;
    }
}

}