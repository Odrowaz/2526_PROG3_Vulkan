#pragma once
#include "VulkanPipeline.h"

class Material {
public:
  Material(VulkanPipeline& InPipeline, const std::vector<VkImageView> &TextureImageViews, const std::vector<VkSampler> &TextureSamplers);
  virtual ~Material();

  virtual void Bind(VkCommandBuffer InCommand);

  VulkanPipeline& GetPipeline() const {
    return Pipeline;
  }


private:
  VkDevice Device = VK_NULL_HANDLE;
  VulkanPipeline& Pipeline;
  VkDescriptorSet DescriptorSet = VK_NULL_HANDLE;
};