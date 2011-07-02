<xsl:stylesheet version="1.1" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:exsl="http://exslt.org/common" extension-element-prefixes="exsl">
<xsl:import href="exsl.xsl"/>

<xsl:template name="ShellWorkItem.cs">
<xsl:param name="ApplicationID"/><xsl:param name="ApplicationName"/>using System;
using System.Collections.Generic;
using System.Text;
using Microsoft.Practices.CompositeUI;
// Menu functionality
using System.IO;
using System.Windows.Forms;
using System.Xml.Serialization;
using Microsoft.Practices.CompositeUI.UIElements;
using Microsoft.Practices.CompositeUI.WinForms;
using Microsoft.Practices.ObjectBuilder;

namespace ShellApplication
{
	public class ShellWorkItem: WorkItem
	{
        protected override void OnRunStarted()
        {
            base.OnRunStarted();
            Items.AddNew&lt;MainController&gt;();
            ProcessCommandMap();
            Activate();
        }

        /// Loads the comand configuration file, and processes
        /// each element in the file. Each element will become a menu
        /// item registered with the UIElement service, attached to the
        /// extension site defined in the XML file. (Note: For this example
        /// they are all added to the extension site named "File" that was added
        /// in CommandsApplication.AfterShellCreated.
        private void ProcessCommandMap()
        {
            CommandMap map = LoadCommandMap();

            foreach (Mapping mapping in map.Mapping)
            {
                ToolStripMenuItem item = CreateMenuItemForMapping(mapping);
                UIExtensionSites[mapping.Site].Add(item);
                Commands[mapping.CommandName].AddInvoker(item, "Click");
            }
        }

        /// &lt;summary&gt;
        /// Creates a new ToolStripMenuItem for the given Mapping from the XML file.
        /// &lt;/summary&gt;
        /// &lt;param name="mapping"&gt;&lt;/param&gt;
        /// &lt;returns&gt;&lt;/returns&gt;
        private ToolStripMenuItem CreateMenuItemForMapping(Mapping mapping)
        {
            ToolStripMenuItem item = new ToolStripMenuItem();
            item.Text = mapping.Label;
            return item;
        }

        /// &lt;summary&gt;
        /// Loads the command map from the configuration file.
        /// &lt;/summary&gt;
        /// &lt;returns&gt;&lt;/returns&gt;
        private CommandMap LoadCommandMap()
        {
            CommandMap map;
            using (Stream stream = new FileStream("CommandMap.xml", FileMode.Open, FileAccess.Read))
            {
                XmlSerializer serializer = new XmlSerializer(typeof(CommandMap));
                map = (CommandMap)serializer.Deserialize(stream);
            }
            return map;
        }
	}
}
</xsl:template>
</xsl:stylesheet>