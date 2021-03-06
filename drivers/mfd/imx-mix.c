// SPDX-License-Identifier: GPL-2.0-only
/*
 * Copyright 2019 NXP.
 */

#include <linux/clk.h>
#include <linux/clk-provider.h>
#include <linux/err.h>
#include <linux/io.h>
#include <linux/module.h>
#include <linux/of_address.h>
#include <linux/spinlock.h>
#include <linux/types.h>
#include <linux/platform_device.h>
#include <linux/of_platform.h>

#include <linux/mfd/core.h>

static int imx_mix_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct resource *res;
	void __iomem *base;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	base = devm_ioremap_resource(dev, res);
	if (IS_ERR(base))
		return PTR_ERR(base);

	dev_set_drvdata(dev, base);

	return devm_of_platform_populate(dev);
}

static const struct of_device_id imx_mix_of_match[] = {
	{ .compatible = "fsl,imx8mp-mix" },
	{ /* Sentinel */ },
};
MODULE_DEVICE_TABLE(of, imx_mix_of_match);

static struct platform_driver imx_mix_driver = {
	.probe = imx_mix_probe,
	.driver = {
		.name = "imx-mix",
		.of_match_table = of_match_ptr(imx_mix_of_match),
	},
};
module_platform_driver(imx_mix_driver);
