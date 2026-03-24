import React, { useEffect, useState } from 'react';
import { useTranslation } from 'react-i18next';
import { Loader2, Globe } from 'lucide-react';
import { useAnimation } from '../../../../contexts/AnimationContext';
import { invoke } from '@tauri-apps/api/core';
import toast from 'react-hot-toast';

interface WorldItem {
  name: string;
  last_played: string;
}

interface WorldsSectionProps {
  modpackId: string;
}

const WorldsSection: React.FC<WorldsSectionProps> = ({ modpackId }) => {
  const { t } = useTranslation();
  const { getAnimationClass, getAnimationStyle } = useAnimation();
  const [worlds, setWorlds] = useState<WorldItem[]>([]);
  const [loading, setLoading] = useState(true);

  const fetchWorlds = async () => {
    try {
      setLoading(true);
      const result = await invoke<WorldItem[]>('list_instance_worlds', { modpackId });
      setWorlds(result);
    } catch (err) {
      console.error('Failed to fetch worlds:', err);
      toast.error(t('modpacks.failedToLoadWorlds', { defaultValue: 'Failed to load worlds' }));
    } finally {
      setLoading(false);
    }
  };

  useEffect(() => {
    fetchWorlds();
  }, [modpackId]);

  const formatDate = (dateStr: string) => {
    try {
      const date = new Date(dateStr);
      return date.toLocaleDateString(undefined, { 
        year: 'numeric', 
        month: 'short', 
        day: 'numeric',
        hour: '2-digit',
        minute: '2-digit'
      });
    } catch {
      return dateStr;
    }
  };

  return (
    <div
      className={`space-y-4 ${getAnimationClass('transition-all duration-200')}`}
      style={getAnimationStyle({
        animation: `fadeInUp 0.3s ease-out 0.1s backwards`
      })}
    >
      <div className="flex items-center justify-between">
        <h3 className="text-lg font-semibold text-white flex items-center space-x-2">
          <Globe className="w-5 h-5 text-lumina-400" />
          <span>{t('modpacks.worlds', { defaultValue: 'Worlds' })}</span>
          <span className="text-sm text-dark-400">({worlds.length})</span>
        </h3>
      </div>

      {loading ? (
        <div className="flex items-center justify-center py-12">
          <Loader2 className="w-8 h-8 text-lumina-500 animate-spin" />
        </div>
      ) : worlds.length === 0 ? (
        <div className="text-center py-12 text-dark-400">
          {t('modpacks.noWorldsFound', { defaultValue: 'No worlds found in this instance.' })}
        </div>
      ) : (
        <div className="grid grid-cols-1 sm:grid-cols-2 gap-4 max-h-[500px] overflow-y-auto scrollbar-thin p-1">
          {worlds.map((world) => (
            <div 
              key={world.name} 
              className="p-4 bg-dark-800/50 hover:bg-dark-800 border border-dark-700 hover:border-dark-600 rounded-xl transition-all group flex items-start space-x-3"
            >
              <div className="p-2 bg-dark-700 rounded-lg text-dark-300 group-hover:text-lumina-400 transition-colors">
                <Globe className="w-5 h-5" />
              </div>
              <div className="flex-1 min-w-0">
                <h4 className="text-sm font-semibold text-white title truncate">
                  {world.name}
                </h4>
                <p className="text-xs text-dark-400 mt-1">
                  {t('modpacks.lastPlayed', { defaultValue: 'Last Played' })}: {formatDate(world.last_played)}
                </p>
              </div>
            </div>
          ))}
        </div>
      )}
    </div>
  );
};

export default WorldsSection;
