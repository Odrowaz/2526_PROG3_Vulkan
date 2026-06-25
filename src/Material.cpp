#include "Material.h"
#include "Common.h"
#include <vector>
#include <vulkan/vulkan.h>
#include "VulkanContext.h"
#include "VulkanPipeline.h"

Material::Material(VulkanPipeline& InPipeline,
                   const std::vector<VkImageView> &TextureImageViews, const std::vector<VkSampler> &TextureSamplers)
    : Device(VulkanContext::GetInstance().GetDevice()), Pipeline(InPipeline) {

  VkDescriptorSetAllocateInfo AllocInfo{};
  AllocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
  AllocInfo.descriptorPool = VulkanContext::GetInstance().GetDescriptorPool();
  AllocInfo.descriptorSetCount = 1;
  AllocInfo.pSetLayouts = InPipeline.GetDescriptorSetLayout();

  CHECK_VK(vkAllocateDescriptorSets(Device, &AllocInfo, &DescriptorSet),
           "Failed to allocate descriptor set");

  std::vector<VkDescriptorImageInfo> ImageInfos(TextureImageViews.size());
  std::vector<VkWriteDescriptorSet> DescriptorWrites(TextureImageViews.size());

  for (size_t i = 0; i < TextureImageViews.size(); ++i) {
    ImageInfos[i] = {};
    ImageInfos[i].imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
    ImageInfos[i].imageView = TextureImageViews[i];
    ImageInfos[i].sampler = TextureSamplers[i];

    DescriptorWrites[i] = {};
    DescriptorWrites[i].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    DescriptorWrites[i].dstSet = DescriptorSet;
    DescriptorWrites[i].dstBinding = i;
    DescriptorWrites[i].dstArrayElement = 0;
    DescriptorWrites[i].descriptorType =
        VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
    DescriptorWrites[i].descriptorCount = 1;
    DescriptorWrites[i].pImageInfo = &ImageInfos[i];
  }

  vkUpdateDescriptorSets(Device, TextureImageViews.size(), DescriptorWrites.data(), 0, nullptr);
}

Material::~Material() {
  vkFreeDescriptorSets(Device, VulkanContext::GetInstance().GetDescriptorPool(), 1, &DescriptorSet);
}

void Material::Bind(VkCommandBuffer InCmd) {
    Pipeline.Bind(InCmd);
    vkCmdBindDescriptorSets(InCmd, VK_PIPELINE_BIND_POINT_GRAPHICS,
                          this->Pipeline.GetPipelineLayout(), 0, 1, &DescriptorSet,
                          0, nullptr);
}