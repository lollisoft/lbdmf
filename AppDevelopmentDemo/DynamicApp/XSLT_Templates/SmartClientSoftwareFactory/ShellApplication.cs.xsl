<xsl:stylesheet version="1.1" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:exsl="http://exslt.org/common" extension-element-prefixes="exsl">
<xsl:import href="exsl.xsl"/>

<xsl:template name="ShellApplication.cs">
<xsl:param name="ApplicationID"/><xsl:param name="ApplicationName"/>using System;
using System.Collections.Generic;
using System.Text;
using Microsoft.Practices.CompositeUI.WinForms;
// Required for the Menu creation
using System.Windows.Forms;
using Microsoft.Practices.CompositeUI;
using Microsoft.Practices.CompositeUI.Commands;
using Microsoft.Practices.CompositeUI.WinForms;
using Microsoft.Practices.CompositeUI.UIElements;


namespace ShellApplication
{
	// Searched for CompositeUI and Ribbon: http://www.google.de/#sclient=psy&hl=de&source=hp&q=CompositeUI+Ribbon&pbx=1&oq=CompositeUI+Ribbon&aq=f&aqi=&aql=&gs_sm=e&gs_upl=3631l13071l0l13519l18l17l0l1l1l0l391l2351l6.8.2.1l17l0&bav=on.2,or.r_gc.r_pw.&fp=1b14abf9aeab93e7&biw=1920&bih=953
	// There is a Ribbon based sample that may be of interest: http://social.msdn.microsoft.com/Forums/da-DK/outlookdev/thread/846d64bd-5995-4bf3-8cfe-c3746e3fbf41
	// Also there is a DevExpress CAB Extension Kit: http://cabdevexpress.codeplex.com/ and some improvements: http://devlynx.livejournal.com/6801.html
	public class ShellApplication : FormShellApplication&lt;ShellWorkItem, ShellForm&gt;
	{
		[STAThread]
		static void Main()
		{
			new ShellApplication().Run();
		}

		/// &lt;summary&gt;
		/// Once the shell is created, we will create a UIElementExtention point
		/// under the File menu that the MainWorkItem can use to add menu items.
		/// &lt;/summary&gt;
		protected override void  AfterShellCreated()
		{
			base.AfterShellCreated();

			ToolStripMenuItem fileItem = (ToolStripMenuItem)Shell.MainMenuStrip.Items["File"];
			RootWorkItem.UIExtensionSites.RegisterSite("File", fileItem.DropDownItems);
		}
		
		#region Unhandled Exception
		
		public override void OnUnhandledException(object sender, UnhandledExceptionEventArgs e)
		{
			Exception ex = e.ExceptionObject as Exception;

			if (ex != null)
			{
				MessageBox.Show(BuildExceptionString(ex));
			}
			else
			{
				MessageBox.Show("An Exception has occured, unable to get details");
			}

			Environment.Exit(0);
		}

		private string BuildExceptionString(Exception exception)
		{
			string errMessage = string.Empty;

			errMessage +=
				exception.Message + Environment.NewLine + exception.StackTrace;

			while (exception.InnerException != null)
			{
				errMessage += BuildInnerExceptionString(exception.InnerException);

				exception = exception.InnerException;
			}

			return errMessage;
		}

		private string BuildInnerExceptionString(Exception innerException)
		{
			string errMessage = string.Empty;

			errMessage += Environment.NewLine + " InnerException ";
			errMessage += Environment.NewLine + innerException.Message + Environment.NewLine + innerException.StackTrace;

			return errMessage;
		} 
		#endregion
	}
}
</xsl:template>
</xsl:stylesheet>