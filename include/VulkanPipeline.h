#pragma once
#include <glm/glm.hpp>
#include <string>
#include <vulkan/vulkan.h>

struct PushConstants {
  VkShaderStageFlagBits stage;
  size_t size;
  size_t offset;
  void *data;
};

class VulkanPipeline {
public:
  VulkanPipeline(std::string VertexShaderPath,
                 std::string FragmentShaderPath, int MaxViews);
  ~VulkanPipeline();

  VkDescriptorSetLayout* GetDescriptorSetLayout() {
    return &DescriptorSetLayout;
  }

  VkPipelineLayout& GetPipelineLayout() {
    return PipelineLayout;
  }

  void Bind(VkCommandBuffer InCmd);
  void SetPushConstants(VkCommandBuffer InCmd, std::vector<PushConstants> PushDatas);

private:
  VkDevice Device = VK_NULL_HANDLE;
  VkPipeline GraphicsPipeline = VK_NULL_HANDLE;
  VkPipelineLayout PipelineLayout = VK_NULL_HANDLE;

  VkDescriptorSetLayout DescriptorSetLayout = VK_NULL_HANDLE;

  VkShaderModule CreateShaderModule(const std::string &InPath);
};