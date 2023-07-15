#include "ProjectManager.h"

ProjectManager::ProjectManager()
{
}

ProjectManager::~ProjectManager()
{
}

void ProjectManager::openProject()
{
    DBG("Project is being opened");
    chooser = std::make_unique<juce::FileChooser>("Select a project file to open...", juce::File{}, "*.asap,");

    auto chooserFlags = juce::FileBrowserComponent::openMode
        | juce::FileBrowserComponent::canSelectFiles;

    chooser->launchAsync(chooserFlags, [this](const juce::FileChooser& fc)
        {
            auto file = fc.getResult();

            if (file != juce::File{})
            {
                DBG("Project was opened");
            }
        });
}

void ProjectManager::saveProject()
{
    DBG("Project is being saved");
    chooser = std::make_unique<juce::FileChooser>("Save project file...", juce::File{}, "*.asap,");

    auto chooserFlags = juce::FileBrowserComponent::openMode
        | juce::FileBrowserComponent::canSelectFiles;

    chooser->launchAsync(chooserFlags, [this](const juce::FileChooser& fc)
        {
            auto file = fc.getResult();

            if (file != juce::File{})
            {
                DBG("Project was saved");
            }
        });
}
